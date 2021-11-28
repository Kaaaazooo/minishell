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

int	ft_echo(const char **argv)
{
	int	i;

	i = 0;
	if (argv[1] != NULL && !ft_strcmp(argv[1], "-n"))
		i++;
	while (argv[++i])
	{
		write(1, argv[i], ft_strlen((char *)argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
	}
	if (argv[1] != NULL && !ft_strcmp(argv[1], "-n"))
		return (0);
	write(1, "\n", 1);
	return (0);
}
