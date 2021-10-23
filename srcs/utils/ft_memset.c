/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:14:47 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/12 18:21:09 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	*str;

	i = 0;
	uc = (unsigned char)c;
	str = (unsigned char *)b;
	while (i < len)
	{
		str[i] = uc;
		i++;
	}
	return (b);
}
