/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:01:06 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/19 14:01:22 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	merge_env(t_m_char **m_str, char *env_var, size_t *i, size_t j)
{
	t_m_char	*new;
	size_t		n;

	if (env_var)
		n = m_strlen(*m_str) + ft_strlen(env_var) - j;
	else
		n = m_strlen(*m_str) - j + 1;
	new = ft_calloc(n, sizeof(t_m_char));
	if (new == NULL)
		return (-1);
	n = 0;
	while ((*m_str)[n].c && n < *i - 1)
	{
		new[n] = (*m_str)[n];
		++n;
	}
	if (env_var)
		while (*env_var)
			new[n++].c = *env_var++;
	while ((*m_str)[*i + j].c)
		new[n++] = (*m_str)[*i + j++];
	free(*m_str);
	*m_str = new;
	return (0);
}
