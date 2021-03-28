/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_modifiers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:39:18 by sabrugie          #+#    #+#             */
/*   Updated: 2021/03/08 12:39:19 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_lli	get_arg(va_list ap, t_modif *mod)
{
	t_lli		arg;

	if (mod->flags & L)
		arg = (t_lli)va_arg(ap, long int);
	else if (mod->flags & LL)
		arg = (t_lli)va_arg(ap, t_lli);
	else if (mod->flags & H)
		arg = (t_lli)(short)va_arg(ap, int);
	else if (mod->flags & HH)
		arg = (t_lli)(signed char)va_arg(ap, int);
	else
		arg = (t_lli)va_arg(ap, int);
	if (arg < 0)
		mod->flags |= MINUS;
	if (mod->flags & MINUS)
		mod->field_width--;
	else if (mod->flags & PLUS)
		mod->field_width--;
	else if (mod->flags & SPACE)
		mod->field_width--;
	return (arg);
}

t_llui	u_get_arg(va_list ap, t_modif *mod)
{
	t_llui		arg;

	if (mod->flags & L)
		arg = (t_llui)va_arg(ap, long unsigned int);
	else if (mod->flags & LL)
		arg = (t_llui)va_arg(ap, t_llui);
	else if (mod->flags & H)
		arg = (t_llui)(short unsigned)va_arg(ap, int);
	else if (mod->flags & HH)
		arg = (t_llui)(unsigned char)va_arg(ap, int);
	else
		arg = (t_llui)va_arg(ap, unsigned int);
	if (arg == 0)
		mod->flags -= mod->flags & ALT_FORM ? ALT_FORM : 0;
	return (arg);
}

t_lli	n_get_arg(t_modif *mod)
{
	t_lli		arg;

	if (mod->flags & L)
		arg = (t_lli)(long int)mod->count;
	if (mod->flags & LL)
		arg = (t_lli)(long long int)mod->count;
	if (mod->flags & H)
		arg = (t_lli)(signed char)mod->count;
	if (mod->flags & HH)
		arg = (t_lli)(short int)mod->count;
	else
		arg = (t_lli)mod->count;
	return (arg);
}

double	d_get_arg(va_list ap, t_modif *mod)
{
	double		arg;

	arg = va_arg(ap, double);
	if (arg < 0)
	{
		if (mod->flags & PLUS)
			mod->flags -= PLUS;
		if (mod->flags & SPACE)
			mod->flags -= SPACE;
	}
	if (mod->flags & PLUS)
		mod->field_width--;
	else if (mod->flags & SPACE)
		mod->field_width--;
	if (!(mod->flags & PREC))
		mod->precision = 6;
	return (arg);
}
