/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_str_conversions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:59:15 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/19 14:07:10 by sabrugie         ###   ########.fr       */
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
