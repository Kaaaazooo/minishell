/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 11:04:04 by sabrugie          #+#    #+#             */
/*   Updated: 2021/09/23 11:50:59 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count(t_line_char *s, char c)
{
	size_t	count;

	count = 0;
	while (s->c)
	{
		while (s->c == c)
			s++;
		count++;
		while (s->c && (s->c != c || s->flag & M_QUOTED
				|| s->flag & M_D_QUOTED
				|| s->flag & M_ESCAPED))
			s++;
	}
	return (count);
}

char	**free_strs(char **strs, int j)
{
	while (j >= 0)
		free(strs[j--]);
	free(strs);
	return (NULL);
}

char	*lcndup(t_line_char *s, int n)
{
	char	*new;
	int		i;

	new = ft_calloc(n + 1, 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new[i] = s[i].c;
		++i;
	}
	return (new);
}

char	**line_split(char **res, t_line_char *s, char c)
{
	size_t	i;
	size_t	j;

	if (s)
		res = ft_calloc((count(s, c) + 1), sizeof(char *));
	if (!s || !res)
		return (NULL);
	j = 0;
	while (s->c)
	{
		while (s->c == c)
			s++;
		i = 0;
		if (s->c)
		{
			while (s[i].c && (s[i].c != c || s[i].flag & M_QUOTED
					|| s[i].flag & M_D_QUOTED || s[i].flag & M_ESCAPED))
				i++;
			res[j++] = lcndup(s, i);
			if (!res)
				return (free_strs(res, (int)(j - 1)));
			s += i;
		}
	}
	return (res);
}
