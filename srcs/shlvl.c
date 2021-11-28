/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:59:20 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/28 12:34:12 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shltermios(int ac, char **av, struct termios *t)
{
	(void)ac;
	(void)av;
	tcgetattr(0, t);
	t->c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, t);
}

int	set_new_shlvl(int lvl)
{
	char	new[32];

	ft_memset(new, 0, 32 * sizeof(char));
	ft_strcpy(new, "SHLVL=");
	if (lvl < 1000)
		ft_itoa(new + 6, lvl);
	if (lvl > 1000)
		ft_itoa(new + 6, 1);
	if (ft_putenv(new))
		return (-1);
	return (0);
}

int	get_shlvl(char *shlvl)
{
	long long int	lvl;
	int				sign;

	if (shlvl == NULL)
		return (set_new_shlvl(1));
	sign = 0;
	lvl = (*shlvl == 0 || (*shlvl == '-' && *(shlvl + 1) == 0));
	if (!(*shlvl == 0 || (*shlvl == '-' && *(shlvl + 1) == 0)))
	{
		if (*shlvl == '-')
			sign = *shlvl++ == '-';
		while (*shlvl >= '0' && *shlvl <= '9' && lvl < 999)
			lvl = lvl * 10 + *shlvl++ - '0';
		if (sign == 0 && lvl >= 1000)
			minishell_error("minishell", "warning",
				"shell level too high, resetting to 1");
		if (*shlvl == 0 && sign)
			lvl = 0;
		else
			++lvl;
	}
	if (set_new_shlvl((int)lvl))
		return (-1);
	return (0);
}
