/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:41:20 by sabrugie          #+#    #+#             */
/*   Updated: 2021/03/08 12:41:21 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}
