/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:35:26 by sabrugie          #+#    #+#             */
/*   Updated: 2019/10/23 11:33:08 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*str;
	size_t			total;
	size_t			i;

	i = 0;
	total = count * size;
	if (!(str = malloc(total)))
		return (0);
	while (i < total)
		str[i++] = 0;
	return ((void*)str);
}
