/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 14:36:13 by sabrugie          #+#    #+#             */
/*   Updated: 2020/02/01 14:35:48 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_d_parts	get_dparts(double nb, t_modif *mod)
{
	t_dtoi64	conv;
	t_d_parts	parts;

	conv.d = nb;
	if ((parts.sign = conv.i & (1LL << 63) ? 1 : 0))
	{
		mod->flags |= MINUS;
		mod->field_width--;
	}
	parts.exponent = (conv.i >> 52) & 0x7FF;
	parts.mantissa = conv.i & ((1LL << 52) - 1);
	if (parts.exponent == 2047)
		return (parts);
	if (parts.exponent == 0)
		parts.exponent = -1022;
	else
	{
		parts.exponent -= 1023;
		parts.mantissa = (1LL << 52) + parts.mantissa;
	}
	return (parts);
}

int			nan_inf(char *str, t_d_parts parts, t_modif *mod)
{
	if (parts.exponent != 0x7FF)
		return (0);
	mod->precision = 0;
	if (mod->flags & ZERO)
		mod->flags -= ZERO;
	if (parts.mantissa == 0)
		return ((int)ft_strlcpy(str, "inf", 4));
	else
	{
		if (mod->flags & PLUS || mod->flags & SPACE)
			mod->field_width++;
		if (mod->flags & PLUS)
			mod->flags -= PLUS;
		if (mod->flags & SPACE)
			mod->flags -= SPACE;
		return ((int)ft_strlcpy(str, "nan", 4));
	}
}

void		insert_bits(uint32_t value, int32_t shift_nb, uint32_t *array,
																	uint32_t n)
{
	t_i64_parts	shift;
	uint32_t	product_low;
	uint32_t	product_high;
	uint64_t	product;
	uint32_t	high_index;

	if (shift_nb <= 0)
		return ;
	shift.low = shift_nb & (W_SHIFT - 1);
	shift.high = shift_nb / W_SHIFT;
	product = (uint64_t)value << shift.low;
	product_low = (uint32_t)product;
	product_high = (uint32_t)(product >> W_SHIFT);
	high_index = n - 1 - shift.high;
	if (high_index < n)
		array[high_index] |= product_high;
	if (high_index + 1 < n)
		array[high_index + 1] |= product_low;
}

int			ft_is_empty(uint32_t *array, uint32_t n)
{
	uint32_t	i;

	i = 0;
	while (i < n)
		if (array[i++])
			return (0);
	return (1);
}

int			ft_dtoa(char *str, double nb, t_modif *mod)
{
	int			i;
	uint32_t	array[34];
	t_d_parts	parts;
	t_i64_parts	mantissa;

	ft_bzero(array, 34 * 4);
	parts = get_dparts(nb, mod);
	if ((i = nan_inf(str, parts, mod)))
		return (i);
	mantissa.high = (uint32_t)(parts.mantissa >> 32);
	mantissa.low = (uint32_t)(parts.mantissa & 0xFFFFFFFF);
	insert_bits(mantissa.high, 12 + parts.exponent, array, 32);
	insert_bits(mantissa.low, 12 + parts.exponent - 32, array, 32);
	str[i++] = '0' + div_remainder(10, array, 32);
	while (!ft_is_empty(array, 32))
		str[i++] = '0' + div_remainder(10, array, 32);
	ft_strrev(str);
	str[i++] = '.';
	ft_bzero(array, 34 * 4);
	insert_bits(mantissa.high, 36 * W_SHIFT - (52 - parts.exponent), array, 34);
	insert_bits(mantissa.low, 35 * W_SHIFT - (52 - parts.exponent), array, 34);
	while (!ft_is_empty(array, 34))
		str[i++] = '0' + mult_overflow(10, array, 34);
	return (i);
}
