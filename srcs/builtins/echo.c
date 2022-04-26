/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moakouda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:58:40 by moakouda          #+#    #+#             */
/*   Updated: 2021/11/26 20:58:41 by moakouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_flag_n(const char *argv)
{
	int	i;

	i = 0;
	if (argv[i] == '-' && argv[i + 1] == 'n')
	{
		i = 1;
		while (argv[i] == 'n')
			i++;
		if (!argv[i])
			return (1);
	}
	return (0);
}

int	ft_echo(const char **argv)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (n == i && argv[++i])
		if (ft_is_flag_n(argv[i]))
			n++;
	while (argv[i])
	{
		write(1, argv[i], ft_strlen((char *)argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n)
		return (0);
	write(1, "\n", 1);
	return (0);
}
