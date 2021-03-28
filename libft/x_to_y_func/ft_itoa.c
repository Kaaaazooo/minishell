/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:18:57 by sabrugie          #+#    #+#             */
/*   Updated: 2019/11/05 17:56:24 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				get_size(int n)
{
	int				len;
	unsigned int	nb;

	len = 0;
	nb = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		nb = (unsigned int)(n * -1);
	}
	else
		nb = (unsigned int)n;
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char					*ft_itoa(int n)
{
	unsigned int	nb;
	int				neg;
	int				len;
	char			*str;

	neg = 0;
	len = get_size(n);
	if (!(str = malloc(sizeof(*str) * ((len + 1)))))
		return (0);
	str[len] = 0;
	if (n < 0)
	{
		neg = 1;
		nb = (unsigned int)(n * -1);
		str[0] = '-';
	}
	else
		nb = (unsigned int)n;
	while (len-- > neg)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (str);
}
