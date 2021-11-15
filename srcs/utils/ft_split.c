/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:52:38 by sabrugie          #+#    #+#             */
/*   Updated: 2021/05/29 14:40:14 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	count(char const *s, char c)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

char	**split_alloc(char const *s, char c)
{
	char	**res;

	if (s)
		res = (char **)ft_calloc(sizeof(char *), (count(s, c) + 1));
	else
	{
		res = (char **)ft_calloc(2, sizeof(char *));
		*res = (char *)ft_calloc(1, sizeof(char));
		if (res == NULL)
			return (NULL);
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char		**res;
	size_t		i;
	size_t		j;

	res = split_alloc(s, c);
	if (!s || !res)
		return (res);
	j = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		i = 0;
		if (*s)
		{
			while (s[i] && s[i] != c)
				i++;
			res[j] = ft_strndup(s, i);
			if (!res[j++])
				return (free_strs(res, (int)(j - 1)));
			s += i;
		}
	}
	return (res);
}
