/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:38:01 by sabrugie          #+#    #+#             */
/*   Updated: 2021/03/08 12:38:02 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		p_conv(va_list ap, int base, t_modif *mod)
{
	t_llui		arg;
	char		nb[21];
	int			len;

	arg = (t_llui)va_arg(ap, void*);
	if (!(len = u_number_base(nb, arg, base)))
		return (-1);
	len -= arg == 0 && mod->flags & PREC && mod->precision == 0 ? 1 : 0;
	mod->field_width -= len > mod->precision ? len + 2 : mod->precision + 2;
	if (!(mod->flags & LEFT))
		if (!(apply_field_width(mod, mod->field_width)))
			return (-1);
	if (mod->flags & MINUS)
		check_assign(mod, '-');
	if (!(apply_alt_form(base, mod)))
		return (0);
	if (!(apply_prec(mod, len)))
		return (-1);
	if (!(mod->flags & PREC && mod->precision == 0 && arg == 0))
		if (!(merge_num(nb, len, mod)))
			return (-1);
	if (mod->flags & LEFT)
		if (!(apply_field_width(mod, mod->field_width)))
			return (-1);
	return (mod->count);
}

int		n_conv(va_list ap, t_modif *mod)
{
	t_lli		*ptr;

	ptr = va_arg(ap, long long int *);
	if (ptr)
		*ptr = n_get_arg(mod);
	return (mod->count);
}

int		f_conv(va_list ap, t_modif *mod)
{
	double		arg;
	char		nb[8192];
	int			len;
	t_llui		d_point;

	arg = d_get_arg(ap, mod);
	ft_bzero(nb, 8192);
	len = ft_dtoa(nb, arg, mod);
	round_double(nb, mod->precision, len);
	d_point = (t_llui)(ft_strchr(nb, '.'));
	mod->field_width -= d_point ? mod->precision +
		(d_point - (t_llui)nb + 1) : mod->precision + ft_strlen(nb);
	if (mod->flags & ALT_FORM && (d_point != 0 || !ft_strncmp(nb, "inf", 3) ||
				!ft_strncmp(nb, "nan", 3)))
		mod->flags -= ALT_FORM;
	else if (mod->flags & ALT_FORM && d_point == 0)
		mod->field_width--;
	if (!(pre_flags(10, mod)))
		return (-1);
	if (!(merge_double(nb, len, mod)))
		return (-1);
	if (mod->flags & LEFT)
		if (!(apply_field_width(mod, mod->field_width)))
			return (-1);
	return (mod->count);
}

int		e_conv(va_list ap, t_modif *mod)
{
	double		arg;
	char		nb[8192];
	int			len;
	int			exp;

	arg = d_get_arg(ap, mod);
	ft_bzero(nb, 8192);
	len = ft_dtoa(nb, arg, mod);
	exp = move_dec_point(nb, mod, len);
	round_double(nb, mod->precision, len);
	exp += move_dec_point(nb, mod, len);
	change_mod(nb, exp, mod);
	if (!(pre_flags(10, mod)))
		return (-1);
	if (!(merge_double(nb, len, mod)))
		return (-1);
	if (!(put_exp(exp, nb, mod)))
		return (-1);
	if (mod->flags & LEFT)
		if (!(apply_field_width(mod, mod->field_width)))
			return (-1);
	return (mod->count);
}

int		new_g_conv(va_list ap, t_modif *mod, ...)
{
	char		nb[8192];
	va_list		tmp;
	double		arg;
	int			len;
	int			exp;

	if (mod->precision < 0)
		mod->precision = 6;
	va_start(tmp, mod);
	va_copy(tmp, ap);
	arg = va_arg(tmp, double);
	ft_bzero(nb, 8192);
	len = ft_dtoa(nb, arg, mod);
	exp = move_dec_point(nb, mod, len);
	round_double(nb, mod->precision - 1, len);
	exp += move_dec_point(nb, mod, len);
	if ((len = (int)ft_strlen(nb)) <= mod->precision)
		mod->precision = len - 1;
	va_end(tmp);
	if (is_e_form(nb, exp, len, mod))
		return (e_conv(ap, mod));
	return (f_conv(ap, mod));
}
