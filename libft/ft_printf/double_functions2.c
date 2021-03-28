/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 16:00:27 by sabrugie          #+#    #+#             */
/*   Updated: 2020/02/13 12:40:59 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			merge_double(char *nb, int len, t_modif *mod)
{
	while (*nb && ft_isdigit(*nb) && len--)
		check_assign(mod, *nb++);
	while (*nb && !ft_isdigit(*nb) && len--)
		check_assign(mod, *nb++);
	while (*nb && ft_isdigit(*nb) && len-- && mod->precision--)
		check_assign(mod, *nb++);
	while (mod->precision-- > 0)
		check_assign(mod, '0');
	return (set_dec_point(nb, mod));
}

int			get_decimal_end(char *str, int precision, int len, int *j)
{
	int		i;
	int		check;

	i = 0;
	while (str[i++] != '.')
		;
	i += precision < len ? precision : len;
	if (str[i - 1] == '.')
		i--;
	check = precision == 0 ? is_all_nine(str, i + 1) : is_all_nine(str, i);
	*j = check ? i-- : --i;
	return (i);
}

int			round_double(char *str, int precision, int len)
{
	char	d[8192];
	int		size;
	int		i;
	int		j;

	i = get_decimal_end(str, precision, len, &j);
	size = j;
	if (i + 1 >= len || (str[i + 1] < '5' && str[i + 1] != '.'))
		return (str[i + 1] == '.' ? size : size + 1);
	ft_bzero(d, 8192);
	if ((str[i + 1] - '0') % 10 >= 5)
		d[j--] = (str[i--] - '0' + 1) % 10 + '0';
	else if (str[i + 1] == '.' && ((str[i + 2] - '0') % 10 >= 5) && (str[i + 3]
		|| (str[i] - '0') % 2 == 1))
		d[j--] = (str[i--] - '0' + 1) % 10 + '0';
	while ((d[j + 1] == '0' || (d[j + 1] == '.' && d[j + 2] == '0')) && i >= 0)
	{
		if (str[i] == '.' && i >= 0)
			d[j--] = str[i--];
		d[j--] = (str[i--] - '0' + 1) % 10 + '0';
	}
	d[j] = i < 0 ? '1' : 0;
	while (i >= 0)
		d[j--] = str[i--];
	return ((int)ft_strlcpy(str, d, (size_t)size + 2));
}

uint64_t	mult_overflow(uint32_t mult, uint32_t *array, uint32_t n)
{
	int32_t		i;
	uint32_t	overflow;
	uint64_t	product;

	i = (int32_t)n - 1;
	overflow = 0;
	while (i >= 0)
	{
		product = (uint64_t)mult * array[i] + overflow;
		array[i--] = (uint32_t)product;
		overflow = (uint32_t)(product >> W_SHIFT);
	}
	return (overflow);
}

uint64_t	div_remainder(uint32_t divisor, uint32_t *array, uint32_t n)
{
	uint32_t	i;
	uint32_t	remainder;
	uint64_t	dividend;
	uint64_t	quotient;

	i = 0;
	remainder = 0;
	while (i < n)
	{
		dividend = ((uint64_t)remainder << W_SHIFT) + array[i];
		quotient = dividend / divisor;
		remainder = (uint32_t)(dividend % divisor);
		array[i++] = (uint32_t)quotient;
	}
	return (remainder);
}
