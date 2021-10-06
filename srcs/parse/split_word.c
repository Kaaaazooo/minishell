/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:14:47 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/06 19:10:16 by sabrugie         ###   ########.fr       */
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

void	quoted(char *buf, char **quote_end)
{
	char	c;

	if (*buf != '\'' && *buf != '"')
		return ;
	if (*quote_end >= buf)
		return ;
	c = *buf++;
	while (*buf != c)
		++buf;
	*quote_end = buf;
}

uint32_t	count_words(char *buf)
{
	uint32_t	count;
	char		*quote_end;

	quote_end = buf;
	count = 0;
	while (*buf)
	{
		while (*buf && is_metachar(buf) && buf >= quote_end)
		{
			if (buf >= quote_end)
			{
				if (is_metachar(buf) == G_GREAT || is_metachar(buf) == L_LESS)
					++buf;
				if (is_metachar(buf) != BLANK)
					++count;
			}
			++buf;
		}
		++count;
		while (*buf && ((!is_metachar(buf)) || buf < quote_end))
			quoted(buf++, &quote_end);
	}
	return (count);
}

char	**split_word(char *buf)
{
	printf("nb of words = %u\n", count_words(buf));
	return (NULL);
}
