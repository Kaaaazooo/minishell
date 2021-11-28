/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moakouda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:59:04 by moakouda          #+#    #+#             */
/*   Updated: 2021/11/28 13:11:38 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_checkspace(char *str)
{
	while (*str == '\n' || *str == '\f' || *str == '\r'
		|| *str == '\t' || *str == '\v' || *str == ' ')
		str++;
	return (str);
}

static int	ft_checkull(const char *str, int j, int *not_num)
{
	int		i;
	char	*tab;
	int		k;
	int		m;

	m = 0;
	tab = "9223372036854775808";
	i = ft_strlen((char *)str);
	k = ft_strlen(tab);
	if (i < k)
		return (1);
	while (m++ < i)
	{
		if (!(str[m] >= '0' && str[m] <= '9'))
			return (1);
		if (str[m] > tab[m] && j == 1)
			return (!(*not_num = 1));
		if (str[m] > tab[m] && j == -1)
			return (!(*not_num = 1));
	}
	return (1);
}

static int	ft_atoi(const char *str, int *not_num)
{
	int					j;
	unsigned long long	nb;

	j = 1;
	nb = 0;
	str = ft_checkspace((char *)str);
	if (*str == '-')
		j = -1;
	if (*str == '+' || *str == '-')
		str++;
	if (!ft_checkull(str, j, not_num))
		return (0);
	while (*str && *str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + (*str - '0');
		if (nb > 9223372036854775807 && j == 1)
			*not_num = 1;
		if (nb > 9223372036854775807 && j == -1)
			return (0);
		str++;
	}
	if (*str && !ft_isdigit(*str))
		*not_num = 1;
	return ((int)(nb * j));
}

void	ft_exit(const char **argv)
{
	unsigned long long	nb;
	int					not_num;

	not_num = 0;
	nb = 0;
	if (argv[1])
	{
		if (argv[2])
		{
			minishell_error("minishell", "exit", "too many arguments");
			g_sh.status = 1;
			return ;
		}
		nb = ft_atoi(argv[1], &not_num);
		if (!not_num)
			g_sh.status = nb % 256;
		else
			g_sh.status = 255;
	}
	write(1, "exit\n", 5);
	if (not_num)
		minishell_error("minishell: exit", (char *)argv[1],
			"numeric argument required");
	exit(g_sh.status);
}
