/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:59:15 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/28 19:53:07 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	get_envname(t_m_char **m_str, size_t *i, size_t *j)
{
	*j = 0;
	if ((*m_str)[*i].c >= '0' && (*m_str)[*i].c <= '9')
		*j = 1;
	else if (ft_isalpha((*m_str)[*i].c) || (*m_str)[*i].c == '_')
	{
		while ((*m_str)[*i + (*j)++].c)
			if (!ft_isalnum((*m_str)[*i + *j].c) && (*m_str)[*i + *j].c != '_')
				break ;
	}
	else if (!(*m_str)[*i].c || (*m_str)[*i].c == '$'
		|| (*m_str)[*i].flag & M_QU_END
		|| (*m_str)[*i].flag & M_QU_END)
		return (1);
	return (0);
}

int	expand(t_m_char **m_str, size_t *i)
{
	size_t	j;
	char	tmp;
	char	*str;
	char	*env_var;

	if ((*m_str)[*i].c == '?')
		return (expand_ret(m_str, i));
	if (get_envname(m_str, i, &j))
		return (0);
	tmp = (*m_str)[*i + j].c;
	(*m_str)[*i + j].c = 0;
	str = m_str_to_str(*m_str + *i);
	if (str == NULL)
		return (-1);
	env_var = ft_getenv(str);
	free(str);
	(*m_str)[*i + j].c = tmp;
	if (merge_env(m_str, env_var, i, j))
		return (-1);
	if (env_var)
		*i += ft_strlen(env_var) - 1;
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
