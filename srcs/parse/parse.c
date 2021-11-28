/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:59:15 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/28 19:53:09 by sabrugie         ###   ########.fr       */
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

ssize_t	mark_quoted(t_m_char **marked, char *word, ssize_t i, uint8_t flag)
{
	if (!quote_is_closed(word))
	{
		free(*marked);
		return (-1);
	}
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
	ssize_t		j;
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
			else if (m_str[j].c == '\"')
				j = mark_quoted(&m_str, &(*word)[i][j], j, M_D_QUOTED);
			if (j < 0)
				return (-1);
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
	int		i;

	word = ft_calloc(count_words(buf) + 1, sizeof(char *));
	token = ft_calloc(count_words(buf) + 1, sizeof(t_token));
	if (token == NULL || word == NULL)
	{
		free(word);
		return (NULL);
	}
	word = split_word(&word, buf);
	if (word == NULL || mark_expand(&word, &token) || mark_redir(&token))
	{
		i = 0;
		while (token[i].str)
			free(token[i++].str);
		free(token);
		token = NULL;
		printf("ici\n");
	}
	free_strs(word, count_words(buf));
	return (token);
}
