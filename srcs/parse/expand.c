/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:59:15 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/12 19:04:39 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	merge_env(t_m_char **m_str, char *env, size_t *i, size_t j)
{
	t_m_char	*new;
	size_t		n;

	if (env)
		n = m_strlen(*m_str) + ft_strlen(env) - j;
	else
		n = m_strlen(*m_str) - j;
	new = ft_calloc(n, sizeof(t_m_char));
	if (new == NULL)
		return (-1);
	n = 0;
	while ((*m_str)[n].c && n < *i - 1)
	{
		new[n] = (*m_str)[n];
		++n;
	}
	if (env)
		while (*env)
			new[n++].c = *env++;
	while ((*m_str)[*i + j].c)
		new[n++] = (*m_str)[*i + j++];
	free(*m_str);
	*m_str = new;
	return (0);
}

int	expand_ret(t_m_char **m_str, size_t *i)
{
	char	ret[16];

	ft_memset(ret, 0, 16);
	ft_itoa(ret, g_sh.status);
	if (merge_env(m_str, ret, i, 1))
		return (-1);
	*i += ft_strlen(ret) - 1;
	return (0);
}

int	expand(t_m_char **m_str, size_t *i)
{
	size_t	j;
	char	tmp;
	char	*str;
	char	*env;

	j = 0;
	if ((*m_str)[*i].c == '?')
		return (expand_ret(m_str, i));
	if (ft_isalpha((*m_str)[*i + j].c) || (*m_str)[*i + j].c == '_')
		while ((*m_str)[*i + ++j].c)
			if (!ft_isalnum((*m_str)[*i + j].c) && (*m_str)[*i + j].c != '_')
				break ;
	tmp = (*m_str)[*i + j].c;
	(*m_str)[*i + j].c = 0;
	str = m_str_to_str(*m_str + *i);
	if (str == NULL)
		return (-1);
	env = getenv(str);
	free(str);
	(*m_str)[*i + j].c = tmp;
	if (merge_env(m_str, env, i, j))
		return (-1);
	if (env)
		*i += ft_strlen(env) - 1;
	return (0);
}

void	remove_quote(t_m_char **m_str)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = m_strlen(*m_str);
	while (i < len)
	{
		if ((*m_str)[i].flag ^ M_QU_START && (*m_str)[i].flag ^ M_QU_END)
			(*m_str)[j++] = (*m_str)[i];
		++i;
	}
	(*m_str)[j].c = 0;
	(*m_str)[j].flag = 0;
}

int	expansion(t_token *token, t_m_char **m_str, uint8_t metachar)
{
	size_t	i;

	i = 0;
	while ((*m_str)[i].c)
	{
		if ((*m_str)[i].c == '$' && (*m_str)[i].flag ^ M_QUOTED)
		{
			++i;
			if (expand(m_str, &i))
				return (-1);
		}
		else
			++i;
	}
	remove_quote(m_str);
	if (metachar)
		token->flag = 1;
	token->str = m_str_to_str((*m_str));
	if (token->str == NULL)
		return (-1);
	return (0);
}
