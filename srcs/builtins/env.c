/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moakouda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:58:58 by moakouda          #+#    #+#             */
/*   Updated: 2021/11/26 20:58:59 by moakouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(const char **argv)
{
	int	i;

	i = -1;
	if (argv[1] == NULL)
	{
		while (g_sh.env[++i])
		{
			if (ft_strchr(g_sh.env[i], '='))
			{
				write(1, g_sh.env[i], ft_strlen(g_sh.env[i]));
				write(1, "\n", 1);
			}
		}
	}
	else
	{
		write(2, "minishell: parameter(s) or flag(s) detected\n", 45);
		return (1);
	}
	return (0);
}
