/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:14:47 by sabrugie          #+#    #+#             */
/*   Updated: 2021/12/01 21:04:28 by sabrugie         ###   ########.fr       */
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

uint32_t	count_words(t_m_char *s)
{
	uint32_t	count;

	count = 0;
	while (s->c)
	{
		while (s->c && m_is_metachar(s) && !(s->flag & 13))
		{
			if (!(s->flag & 13))
			{
				if (m_is_metachar(s) == G_GREAT || m_is_metachar(s) == L_LESS)
					++s;
				if (m_is_metachar(s) != BLANK)
					++count;
			}
			++s;
		}
		if (s->c)
			++count;
		while (s->c && (!(m_is_metachar(s)) || s->flag & 13))
			++s;
	}
	return (count);
}

int	incr_index(t_m_char *s, uint32_t *i)
{
	int	ret;

	ret = 0;
	if (!(s->flag & 13))
	{
		if (m_is_metachar(s) == G_GREAT || m_is_metachar(s) == L_LESS)
			ret = 2;
		else if (m_is_metachar(s))
			ret = 1;
		else if (s[1].c && m_is_metachar(s + 1)
			&& m_is_metachar(s + 1) != BLANK)
			ret = 1;
	}
	if (ret == 2)
		++(*i);
	return (ret);
}

int	add_word(t_token **token, t_m_char *s, uint32_t i, uint32_t j)
{
	char		*str;
	char		tmp;
	uint32_t	n;

	tmp = s[i].c;
	s[i].c = 0;
	if (m_is_metachar(s) && m_is_metachar(s) != BLANK && !(s->flag & 15))
		(*token)[j].flag = 1;
	remove_quote(&s);
	str = m_str_to_str(s);
	if (str == NULL)
	{
		n = 0;
		while ((*token)[n].str)
			free((*token)[n++].str);
		free(*token);
		*token = NULL;
		return (-1);
	}
	(*token)[j].str = str;
	s[i].c = tmp;
	return (0);
}

int	split_word(t_token **token, t_m_char *s)
{
	uint32_t	i;
	uint32_t	j;

	j = 0;
	*token = ft_calloc(count_words(s) + 1, sizeof(**token));
	if (*token == NULL)
		return (-1);
	while (s->c)
	{
		while (s->c && !(s->flag & 15) && m_is_metachar(s) == BLANK)
			s++;
		i = 0;
		while (s[i].c && (s[i].flag & 13 || m_is_metachar(&s[i]) != BLANK))
		{
			if (incr_index(&s[i++], &i))
				break ;
		}
		if (s->c == 0)
			break ;
		if (add_word(token, s, i, j++))
			return (-1);
		s += i;
	}
	return (0);
}
