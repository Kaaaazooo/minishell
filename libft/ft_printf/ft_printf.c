/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:40:00 by sabrugie          #+#    #+#             */
/*   Updated: 2021/03/08 12:47:41 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		fill_buf(char conv, va_list ap, t_modif *mod)
{
	if (conv == 'c')
		return (c_conv(ap, mod));
	else if (conv == '%')
		return (percent_conv(mod));
	else if (conv == 's')
		return (s_conv(ap, mod));
	else if (conv == 'd' || conv == 'i')
		return (num_conv(ap, 10, mod));
	else if (conv == 'u')
		return (u_num_conv(ap, 10, mod));
	else if (conv == 'X')
		return (u_num_conv(ap, -16, mod));
	else if (conv == 'x')
		return (u_num_conv(ap, 16, mod));
	else if (conv == 'p')
		return (p_conv(ap, 16, mod));
	else if (conv == 'n')
		return (n_conv(ap, mod));
	else if (conv == 'f')
		return (f_conv(ap, mod));
	else if (conv == 'e')
		return (e_conv(ap, mod));
	else if (conv == 'g')
		return (new_g_conv(ap, mod));
	return (-1);
}

void	get_modifiers(char *format, t_modif *mod, va_list ap)
{
	while (*format)
	{
		if (*format != '%' && *format)
		{
			check_assign(mod, *format++);
			continue ;
		}
		format++;
		mod->flags = get_flags(&format);
		get_field(&format, ap, mod);
		get_precision(&format, ap, mod);
		get_length_modif(&format, mod);
		if (mod->flags & ZERO && mod->flags & PREC &&
				*format != 'c' && *format != '%' && *format != 'f' &&
				*format != 'e' && *format != 'g')
			mod->flags -= ZERO;
		if (fill_buf(*format++, ap, mod) < 0)
			return ;
	}
}

int		ft_printf(const char *format, ...)
{
	t_modif	mod;
	va_list	ap;

	mod.field_width = 0;
	mod.precision = -1;
	mod.flags = 0;
	mod.count = 0;
	va_start(ap, format);
	get_modifiers((char *)format, &mod, ap);
	if (mod.count > 0)
		write(1, mod.buf, mod.count % BUF_SIZE == 0 ?
				BUF_SIZE : mod.count % BUF_SIZE);
	va_end(ap);
	return (mod.count);
}
