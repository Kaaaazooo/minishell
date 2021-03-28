/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:40:41 by sabrugie          #+#    #+#             */
/*   Updated: 2021/03/08 12:40:42 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		nb_len(int nb, int base)
{
	int					len;

	len = 0;
	base *= (base < 0) ? -1 : 1;
	if (nb == 0)
		return (1);
	while (nb)
	{
		len++;
		nb /= base;
	}
	return (len);
}

int		merge_num(char *nb, int len, t_modif *mod)
{
	int					i;

	i = 0;
	while (nb[i] && len--)
		check_assign(mod, nb[i++]);
	return (1);
}

char	*set_base(char *base_str, int base)
{
	if (base == -16)
		ft_memcpy(base_str, "0123456789ABCDEF", 16);
	else
		ft_memcpy(base_str, "0123456789abcdef", 16);
	return (base_str);
}

int		number_base(char *str, t_lli nb, int base)
{
	char				base_str[16];
	char				number[64];
	t_llui				num;
	int					i;
	int					j;

	set_base(base_str, base);
	base *= (base < 0 ? -1 : 1);
	num = nb < 0 && base == 10 ? (t_llui)-nb : (t_llui)nb;
	i = 0;
	j = 0;
	if (num == 0)
		number[i++] = '0';
	while (num)
	{
		number[i++] = base_str[num % base];
		num /= base;
	}
	while (--i > -1)
		str[j++] = number[i];
	return (j);
}

int		u_number_base(char *str, t_llui nb, int base)
{
	char				base_str[16];
	char				number[64];
	int					i;
	int					j;

	set_base(base_str, base);
	base *= (base < 0 ? -1 : 1);
	i = 0;
	j = 0;
	if (nb == 0)
		number[i++] = '0';
	while (nb)
	{
		number[i++] = base_str[nb % base];
		nb /= base;
	}
	while (--i > -1)
		str[j++] = number[i];
	return (j);
}
