/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:50:22 by sabrugie          #+#    #+#             */
/*   Updated: 2021/09/22 18:02:59 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			total;
	size_t			i;

	ptr = (unsigned char *)malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	total = count * size;
	while (i < total)
		ptr[i++] = 0;
	return (ptr);
}
