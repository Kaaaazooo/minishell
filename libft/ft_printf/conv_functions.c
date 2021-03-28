/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:38:11 by sabrugie          #+#    #+#             */
/*   Updated: 2021/03/08 12:38:51 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		c_conv(va_list ap, t_modif *mod)
{
	wchar_t					arg;

	arg = mod->flags & L ? (wchar_t)va_arg(ap, wint_t) :
							(wchar_t)(unsigned char)va_arg(ap, int);
	if (arg > 255 || arg < 0)
		return (-1);
	if (!(mod->flags & LEFT))
		if (!(apply_field_width(mod, mod->field_width - 1)))
			return (-1);
	check_assign(mod, (unsigned char)arg);
	if (mod->flags & LEFT)
		if (!(apply_field_width(mod, mod->field_width - 1)))
			return (-1);
	return (mod->count);
}

int		s_conv(va_list ap, t_modif *mod)
{
	char				*arg;
	int					len;

	arg = va_arg(ap, char *);
	if (arg == NULL)
		arg = "(null)";
	len = get_len(arg, mod);
	if (mod->precision < 0)
		mod->precision = len;
	mod->field_width = (len >= mod->field_width) ? 0 : mod->field_width - len;
	if (!(mod->flags & LEFT))
		if (!(apply_field_width(mod, mod->field_width)))
			return (-1);
	while (len-- && *arg)
		check_assign(mod, *arg++);
	if (mod->flags & LEFT)
		if (!(apply_field_width(mod, mod->field_width)))
			return (-1);
	return (mod->count);
}

int		num_conv(va_list ap, int base, t_modif *mod)
{
	t_lli					arg;
	char					nb[21];
	int						len;

	arg = get_arg(ap, mod);
	len = arg || mod->precision || !(mod->flags & PREC) ?
							number_base(nb, arg, base) : 0;
	mod->field_width -= len > mod->precision ? len : mod->precision;
	if (mod->flags & ZERO)
		if (!(apply_sign(base, mod)))
			return (-1);
	if (!(mod->flags & LEFT))
		if (!(apply_field_width(mod, mod->field_width)))
			return (-1);
	if (!(mod->flags & ZERO))
		if (!(apply_sign(base, mod)))
			return (-1);
	if (!(apply_prec(mod, len)) || !(merge_num(nb, len, mod)))
		return (-1);
	if (mod->flags & LEFT)
		if (!(apply_field_width(mod, mod->field_width)))
			return (-1);
	return (mod->count);
}

int		u_num_conv(va_list ap, int base, t_modif *mod)
{
	t_llui					arg;
	char					nb[21];
	int						len;

	arg = u_get_arg(ap, mod);
	len = arg || mod->precision || !(mod->flags & PREC) ?
							u_number_base(nb, arg, base) : 0;
	mod->field_width -= len > mod->precision ? len : mod->precision;
	if (mod->flags & ALT_FORM && (base == 16 || base == -16))
		mod->field_width -= 2;
	if (mod->flags & ZERO)
		if (!(apply_sign(base, mod)))
			return (-1);
	if (!(mod->flags & LEFT))
		if (!(apply_field_width(mod, mod->field_width)))
			return (-1);
	if (!(mod->flags & ZERO))
		if (!(apply_sign(base, mod)))
			return (-1);
	if (!(apply_prec(mod, len)) || !(merge_num(nb, len, mod)))
		return (-1);
	if (mod->flags & LEFT)
		if (!(apply_field_width(mod, mod->field_width)))
			return (-1);
	return (mod->count);
}

int		percent_conv(t_modif *mod)
{
	if (!(mod->flags & LEFT))
		if (!(apply_field_width(mod, mod->field_width - 1)))
			return (-1);
	check_assign(mod, '%');
	if (mod->flags & LEFT)
		if (!(apply_field_width(mod, mod->field_width - 1)))
			return (-1);
	return (mod->count);
}
