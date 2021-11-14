/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:59:15 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/12 19:04:39 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_m_char	*str_to_m_str(char *str)
{
	size_t		i;
	t_m_char	*m_str;

	m_str = ft_calloc(ft_strlen(str) + 1, sizeof(t_m_char));
	if (m_str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		m_str[i].c = str[i];
		++i;
	}
	return (m_str);
}

char	*m_str_to_str(t_m_char *m_str)
{
	size_t	i;
	char	*str;

	i = 0;
	while (m_str[i].c)
		++i;
	str = ft_calloc(i + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (m_str[i].c)
	{
		str[i] = m_str[i].c;
		++i;
	}
	return (str);
}

size_t	mark_quoted(t_m_char **marked, char *word, size_t i, uint8_t flag)
{
	size_t	j;

	j = 1;
	while (word[j] && word[j] != *word)
		++j;
	if (word[j] == 0)
		return (++i);
	(*marked)[i].c = *(word)++;
	if (!((*marked)[i].flag & M_QUOTED) &&
			!((*marked)[i].flag & M_D_QUOTED))
		(*marked)[i++].flag |= M_QU_START;
	while (*word && ((flag & M_D_QUOTED && *word != '\"')
			|| (flag & M_QUOTED && *word != '\'')))
	{
		(*marked)[i].c = *(word++);
		if (!((*marked)[i].flag & M_QUOTED) &&
				!((*marked)[i].flag & M_D_QUOTED))
			(*marked)[i++].flag |= flag;
	}
	(*marked)[i].c = *(word)++;
	if (!((*marked)[i].flag & M_QUOTED) &&
			!((*marked)[i].flag & M_D_QUOTED))
		(*marked)[i].flag |= M_QU_END;
	return (i);
}

int	mark_expand(char ***word, t_token **token)
{
	size_t		i;
	size_t		j;
	t_m_char	*m_str;

	i = SIZE_MAX;
	j = 0;
	while (j == 0 && (*word)[++i])
	{
		m_str = str_to_m_str((*word)[i]);
		if (m_str == NULL)
			return (-1);
		while ((*word)[i][j])
		{
			if (m_str[j].c == '\'')
				j = mark_quoted(&m_str, &(*word)[i][j], j, M_QUOTED);
			if (m_str[j].c == '\"')
				j = mark_quoted(&m_str, &(*word)[i][j], j, M_D_QUOTED);
			++j;
		}
		j = expansion(&(*token)[i], &m_str, is_metachar((*word)[i]));
		free(m_str);
	}
	return (j);
}

t_token	*parse(char *buf)
{
	char	**word;
	t_token	*token;
	size_t	i;

	errno = 0;
	word = ft_calloc(count_words(buf) + 1, sizeof(char *));
	if (word == NULL)
		return (NULL);
	token = ft_calloc(count_words(buf) + 1, sizeof(t_token));
	if (token == NULL || word == NULL)
	{
		free(word);
		return (NULL);
	}
	split_word(&word, buf);
	i = mark_expand(&word, &token);
	if (i || mark_redir(&token))
	{
		while (token[i].str)
			free(token[i++].str);
		free(token);
		token = NULL;
	}
	free_strs(word, count_words(buf));
	return (token);
}
