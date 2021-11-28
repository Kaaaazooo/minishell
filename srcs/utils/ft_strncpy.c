/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:47:42 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/25 22:47:44 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*p;

	p = dest;
	while (n--)
	{
		*p++ = *src;
		if (*src)
			src++;
	}
	*p = '\0';
	return (dest);
}
