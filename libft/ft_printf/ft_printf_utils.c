/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:39:50 by sabrugie          #+#    #+#             */
/*   Updated: 2021/03/08 12:39:51 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_skipatoi(char **str)
{
	int		nb;
	char	neg;

	nb = 0;
	neg = 0;
	if (**str == '-')
	{
		neg = 1;
		(*str)++;
	}
	while (ft_isdigit(**str))
		nb = nb * 10 + *((*str)++) - '0';
	return (neg ? -nb : nb);
}

void	check_assign(t_modif *mod, char c)
{
	if (mod->count != 0 && mod->count % BUF_SIZE == 0)
		write(1, mod->buf, BUF_SIZE);
	mod->buf[mod->count++ % BUF_SIZE] = c;
}

int		get_len(char *str, t_modif *mod)
{
	int		i;

	i = 0;
	if (str && !(mod->flags & PREC && mod->precision == 0))
	{
		while (str[i] && (i < mod->precision || !(mod->flags & PREC)))
			i++;
	}
	return (i);
}

char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (--i > j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j++] = tmp;
	}
	return (str);
}

int		get_exp(char *nb, t_modif *mod, int len)
{
	char	num[8192];

	ft_strcpy(num, nb);
	return (move_dec_point(num, mod, len));
}
