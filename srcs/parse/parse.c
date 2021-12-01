/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:59:15 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/27 23:12:28 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t	m_is_metachar(t_m_char *m_str)
{
	if (m_str[0].c == '>' && m_str[1].c == '>')
		return (G_GREAT);
	if (m_str[0].c == '<' && m_str[1].c == '<')
		return (L_LESS);
	if (m_str[0].c == '<')
		return (GREAT);
	if (m_str[0].c == '>')
		return (LESS);
	if (m_str[0].c == '|')
		return (PIPE);
	if (m_str[0].c == ' ' || m_str[0].c == '\t')
		return (BLANK);
	return (0);
}

ssize_t	mark_quoted(t_m_char **marked, char *word, ssize_t i, uint8_t flag)
{
	if (!quote_is_closed(word))
		return (-1);
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

int	mark_expand(char *buf, t_m_char **m_buf, t_token **token)
{
	ssize_t	i;

	i = 0;
	while (buf[i])
	{
		if ((*m_buf)[i].c == '\'')
			i = mark_quoted(m_buf, &(buf[i]), i, M_QUOTED);
		else if ((*m_buf)[i].c == '\"')
			i = mark_quoted(m_buf, &(buf[i]), i, M_D_QUOTED);
		if (i < 0)
			return (-1);
		++i;
	}
	if (expansion(m_buf))
		return (-1);
	if (split_word(token, (*m_buf)))
		return (-1);
	return (0);
}

t_token	*parse(char *buf)
{
	t_m_char	*m_buf;
	t_token		*token;
	size_t		i;

	m_buf = str_to_m_str(buf);
	if (m_buf == NULL)
		return (NULL);
	if (mark_expand(buf, &m_buf, &token))
		token = NULL;
	free(m_buf);
	if (token && mark_redir(&token))
	{
		i = 0;
		while (token && token[i].str)
			free(token[i++].str);
		free(token);
		token = NULL;
	}
	return (token);
}
