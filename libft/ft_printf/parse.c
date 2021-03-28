/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:06:46 by sabrugie          #+#    #+#             */
/*   Updated: 2021/03/08 12:41:10 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		get_field(char **s, va_list ap, t_modif *mod)
{
	mod->field_width = 0;
	if (ft_isdigit(**s))
		mod->field_width = ft_skipatoi((char **)s);
	else if (**s == '*')
	{
		mod->field_width = va_arg(ap, int);
		(*s)++;
	}
	if (mod->field_width < 0)
	{
		mod->flags -= mod->flags & ZERO ? ZERO : 0;
		mod->flags |= LEFT;
		mod->field_width *= -1;
	}
}

void		get_precision(char **s, va_list ap, t_modif *mod)
{
	mod->precision = 0;
	if (**s == '.')
	{
		(*s)++;
		mod->flags |= PREC;
		if (ft_isdigit(**s) || **s == '-' || **s == '+')
			mod->precision = ft_skipatoi((char **)s);
		else if (**s == '*')
		{
			mod->precision = va_arg(ap, int);
			(*s)++;
		}
	}
	if (mod->precision < 0)
		mod->flags -= PREC;
}

void		get_length_modif(char **s, t_modif *mod)
{
	if (**s == 'l' && *((*s) + 1) == 'l')
	{
		mod->flags |= LL;
		(*s) += 2;
	}
	else if (**s == 'l')
	{
		mod->flags |= L;
		(*s)++;
	}
	else if (**s == 'h' && *((*s) + 1) == 'h')
	{
		mod->flags |= HH;
		(*s) += 2;
	}
	else if (**s == 'h')
	{
		mod->flags |= H;
		(*s)++;
	}
}

short int	get_flags(char **s)
{
	short int	flags;

	flags = 0;
	while (**s == '-' || **s == '+' || **s == ' ' || **s == '#' || **s == '0')
	{
		if (**s == '-')
			flags |= LEFT;
		else if (**s == '+')
			flags |= PLUS;
		else if (**s == ' ')
			flags |= SPACE;
		else if (**s == '#')
			flags |= ALT_FORM;
		else if (**s == '0')
			flags |= ZERO;
		(*s)++;
	}
	return (flags);
}
