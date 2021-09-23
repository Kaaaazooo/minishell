/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marked_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 11:44:50 by sabrugie          #+#    #+#             */
/*   Updated: 2021/09/23 13:06:43 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_line_char	**free_lctabs(t_line_char **strs, int j)
{
	while (j >= 0)
		free(strs[j--]);
	free(strs);
	return (NULL);
}

t_line_char	*lccpy(t_line_char *dst, t_line_char *src, int n)
{
	int	i;

	if (!dst || !src)
		return (NULL);
	i = 0;
	while (src[i].c && i < n)
	{
		dst[i] = src[i];
		++i;
	}
	return (dst);
}

t_line_char	**marked_split(t_line_char ***res, t_line_char *s, char c)
{
	size_t		i;
	size_t		j;

	if (!*res)
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
			(*res)[j] = ft_calloc(i + 1, sizeof(***res));
			if (!*res)
				return (free_lctabs(*res, (int)(j)));
			(*res)[j] = lccpy((*res)[j], s, i);
			++j;
			s += i;
		}
	}
	return (*res);
}
