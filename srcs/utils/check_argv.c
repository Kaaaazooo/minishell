/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:45:58 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/25 22:45:59 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

int	check_argv(char *str, int mode)
{
	if (ft_isdigit(*str) || *str == '+' || *str == '=')
		return (1);
	while (*str != '\0')
	{
		if (mode && (*str == '=' || (*str == '+' && *(str + 1) == '=')))
			return (0);
		if (!ft_isalnum(*str) && *str != '_')
			return (1);
		str++;
	}
	return (0);
}
