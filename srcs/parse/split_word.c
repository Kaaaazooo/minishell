/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:14:47 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/28 19:53:08 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t	is_metachar(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (G_GREAT);
	if (!ft_strncmp(str, "<<", 2))
		return (L_LESS);
	if (!ft_strncmp(str, ">", 1))
		return (GREAT);
	if (!ft_strncmp(str, "<", 1))
		return (LESS);
	if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	if (*str == ' ' || *str == '\t')
		return (BLANK);
	return (0);
}

char	*quoted(char *buf, char **end_quote)
{
	char	c;

	if (*buf != '\'' && *buf != '"')
		return (*end_quote);
	if (*end_quote >= buf)
		return (*end_quote);
	c = *buf++;
	while (*buf && *buf != c)
		++buf;
	*end_quote = buf;
	return (*end_quote);
}

uint32_t	count_words(char *buf)
{
	uint32_t	count;
	char		*end_quote;

	end_quote = NULL;
	count = 0;
	while (*buf)
	{
		while (*buf && is_metachar(buf) && buf > end_quote)
		{
			if (buf >= end_quote)
			{
				if (is_metachar(buf) == G_GREAT || is_metachar(buf) == L_LESS)
					++buf;
				if (is_metachar(buf) != BLANK)
					++count;
			}
			++buf;
		}
		++count;
		while (*buf && ((!is_metachar(buf)) || buf < end_quote))
			quoted(buf++, &end_quote);
	}
	return (count);
}

int	incr_index(char *s, char **end_quote, uint32_t *i)
{
	int	ret;

	ret = 0;
	if (s > quoted(s, end_quote))
	{
		if (is_metachar(s) == G_GREAT || is_metachar(s) == L_LESS)
			ret = 2;
		else if (is_metachar(s))
			ret = 1;
		else if (s[1] && is_metachar(s + 1)
			&& is_metachar(s + 1) != BLANK)
			ret = 1;
	}
	if (ret == 2)
		++(*i);
	return (ret);
}

char	**split_word(char ***dst, char *s)
{
	uint32_t	i;
	uint32_t	j;
	char		*end_quote;

	j = 0;
	end_quote = NULL;
	while (*s)
	{
		while (*s && s > quoted(s, &end_quote) && is_metachar(s) == BLANK)
			s++;
		i = 0;
		while (s[i] && (&s[i] < quoted(&s[i], &end_quote)
				|| is_metachar(&s[i]) != BLANK))
			if (incr_index(&s[i++], &end_quote, &i))
				break ;
		(*dst)[j++] = ft_strndup(s, i);
		if (!(*dst)[j - 1])
			return (free_strs((*dst), (int)(j - 1)));
		s += i;
	}
	return (*dst);
}
