/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:18:57 by sabrugie          #+#    #+#             */
/*   Updated: 2019/11/24 16:01:00 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				get_size(long long unsigned int n, int len_base)
{
	int				len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / len_base;
		len++;
	}
	return (len);
}

char					*ft_itoa_base(long long unsigned int n, char *base)
{
	int				len;
	int				len_base;
	char			*str;

	if (!base)
		return (0);
	len_base = ft_strlen(base);
	len = get_size(n, len_base);
	if (!(str = malloc(sizeof(*str) * ((len + 1)))))
		return (0);
	str[len] = 0;
	while (len-- > 0)
	{
		str[len] = base[n % len_base];
		n /= len_base;
	}
	return (str);
}
