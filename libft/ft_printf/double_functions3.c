/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_functions3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:58:46 by sabrugie          #+#    #+#             */
/*   Updated: 2020/02/13 12:39:57 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_all_nine(char *str, int n)
{
	int		i;

	i = 0;
	while (str[i] && i < n && str[i] != '.')
	{
		if (str[i++] != '9')
			return (0);
	}
	if (str[i] == '.')
	{
		n++;
		i++;
	}
	if (!str[i])
		return (0);
	while (str[i] && i < n)
	{
		if (str[i++] != '9')
			return (i >= n && str[i - 1] >= '5' ? 1 : 0);
	}
	return (1);
}

int		shift_point_right(char *str, int len)
{
	int		i;
	int		j;
	int		save;
	char	tmp;

	i = (unsigned int)(ft_strchr(str, '.') - str);
	j = i;
	save = i;
	while (ft_atoi(str) == 0 && ++j < len - 1)
	{
		tmp = str[j];
		str[j] = str[i];
		str[i++] = tmp;
	}
	return (i - save);
}

int		shift_point_left(char *str)
{
	int		i;
	int		j;
	int		save;
	char	tmp;

	i = (int)(ft_strchr(str, '.') - str);
	j = i;
	save = i;
	while (--j > 0)
	{
		tmp = str[j];
		str[j] = str[i];
		str[i--] = tmp;
	}
	return (save - i);
}

int		put_exp(int exp, char *nb, t_modif *mod)
{
	int		len;
	char	exponent[16];

	if (!ft_strncmp(nb, "inf", 3) || !ft_strncmp(nb, "nan", 3))
		return (1);
	if (ft_atoi(nb) == 10)
	{
		exp++;
		mod->count--;
	}
	len = number_base(exponent, (int)exp, 10);
	check_assign(mod, 'e');
	check_assign(mod, exp < 0 ? '-' : '+');
	if (exp > -10 && exp < 10)
		check_assign(mod, '0');
	return (!(merge_num(exponent, len, mod)) ? 0 : 1);
}

int		move_dec_point(char *str, t_modif *mod, int len)
{
	char	num[8192];
	int		exp;

	ft_strcpy(num, str);
	exp = 0;
	if (!ft_strchr(num, '.'))
		return (0);
	if (!ft_isdigit(str[0]))
	{
		mod->field_width++;
		return (0);
	}
	if (ft_atoi(str) == 0)
		exp = shift_point_right(num, len) * -1;
	else if (ft_atoi(str) != 0)
		exp = shift_point_left(num);
	if (exp < 0)
		ft_strcpy(str, num + exp * -1);
	else
		ft_strcpy(str, num);
	return (exp);
}
