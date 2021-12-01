/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:18:57 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/20 18:49:25 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static unsigned int	get_size(int n)
{
	unsigned int	len;
	unsigned int	nb;

	len = 0;
	nb = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		nb = n * -1;
	}
	else
		nb = n;
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(char *dst, int n)
{
	unsigned int	nb;
	int				neg;
	int				len;

	neg = 0;
	len = get_size(n);
	dst[len] = 0;
	if (n < 0)
	{
		neg = 1;
		nb = (unsigned int)(n * -1);
		dst[0] = '-';
	}
	else
		nb = (unsigned int)n;
	while (len-- > neg)
	{
		dst[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (dst);
}

static long long unsigned int	llu_get_size(long long unsigned int n)
{
	long long unsigned int	len;
	long long unsigned int	nb;

	len = 0;
	nb = 0;
	if (n == 0)
		return (1);
	nb = n;
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_llutoa(char *dst, long long unsigned int n)
{
	long long unsigned int	nb;
	long long unsigned int	len;

	len = llu_get_size(n);
	dst[len] = 0;
	nb = n;
	while (len--)
	{
		dst[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (dst);
}
