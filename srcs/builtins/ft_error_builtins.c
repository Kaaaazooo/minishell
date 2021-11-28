/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moakouda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 22:25:53 by moakouda          #+#    #+#             */
/*   Updated: 2021/11/28 12:55:58 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_malloc(void)
{
	perror("minishell");
	return (1);
}

int	ft_free_tab_malloc(char **new_env, int i)
{
	free_strs(new_env, i);
	return (ft_error_malloc());
}
