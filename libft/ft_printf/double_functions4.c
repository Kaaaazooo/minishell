/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_functions4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:18:15 by sabrugie          #+#    #+#             */
/*   Updated: 2020/02/02 14:17:17 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_e_form(char *nb, int exp, int len, t_modif *mod)
{
	int		ret;
	int		tmp;
	int		adj;

	(void)len;
	ret = 0;
	tmp = mod->precision;
	while (tmp >= 0 && nb[tmp] == '0')
		tmp--;
	if ((exp < -4 || exp >= mod->precision) && exp != 0)
	{
		adj = (exp + 1) < 0 || tmp - (exp + 1) ? 1 : exp + 1;
		ret = 1;
	}
	else
		adj = tmp - (exp + 1) < 0 ? 1 : exp + 1;
	mod->precision = tmp == exp ? 0 : tmp - adj;
	return (ret);
}

int		set_dec_point(char *nb, t_modif *mod)
{
	(void)nb;
	if (mod->flags & ALT_FORM)
		check_assign(mod, '.');
	return (1);
}

void	change_mod(char *nb, int exp, t_modif *mod)
{
	if (mod->flags & ALT_FORM && ft_strchr(nb, '.'))
		mod->flags -= ALT_FORM;
	if (mod->flags & ALT_FORM)
		mod->field_width--;
	if (!ft_strncmp(nb, "inf", 3) || !ft_strncmp(nb, "nan", 3))
		mod->field_width -= 3;
	else
		mod->field_width -= 4 + mod->precision + nb_len(exp, 10);
	if (exp > -10 && exp < 10)
		mod->field_width--;
	if (mod->precision == 0)
		mod->field_width++;
}
