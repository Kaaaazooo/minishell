/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moakouda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:59:48 by moakouda          #+#    #+#             */
/*   Updated: 2021/11/26 20:59:49 by moakouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_remove(int index)
{
	char	**new_env;
	int		i;

	i = -1;
	new_env = (char **)malloc(sizeof(char *) * (len_array(g_sh.env)));
	if (!new_env)
		return (ft_error_malloc());
	while (++i < len_array(g_sh.env) - 1)
	{
		if (i < index)
			new_env[i] = ft_strdup(g_sh.env[i]);
		else
			new_env[i] = ft_strdup(g_sh.env[i + 1]);
		if (!new_env[i])
		{
			free_strs(g_sh.env, i);
			return (ft_error_malloc());
		}
	}
	free_strs(g_sh.env, i);
	new_env[i] = NULL;
	g_sh.env = new_env;
	return (0);
}

int	ft_do_unset(const char *argv, int *not_valid)
{
	int		i;

	i = -1;
	while (g_sh.env[++i])
	{
		if (!ft_strncmp(argv, g_sh.env[i], ft_strlen((char *)argv)))
		{
			if (ft_remove(i))
				return (1);
			break ;
		}
		else if (check_argv((char *) argv))
		{
			write(2, "minishell: unset: `", 19);
			write(2, argv, ft_strlen((char *)argv));
			minishell_error("'", "not a valid identifier", NULL);
			*not_valid = 1;
			break ;
		}
	}
	return (0);
}

int	ft_unset(const char **argv)
{
	int	cmd;
	int	not_valid;

	cmd = 0;
	not_valid = 0;
	if (!argv[1])
		return (1);
	while (argv[++cmd])
	{
		if (ft_do_unset(argv[cmd], &not_valid))
			return (1);
	}
	return (not_valid);
}
