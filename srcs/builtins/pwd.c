/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moakouda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:59:14 by moakouda          #+#    #+#             */
/*   Updated: 2021/11/26 20:59:17 by moakouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(const char **argv)
{
	char	*path;

	(void )argv;
	path = NULL;
	path = getcwd(path, 32768);
	if (!path)
		return (ft_error_malloc());
	write(1, path, ft_strlen(path));
	free(path);
	write(1, "\n", 1);
	return (0);
}
