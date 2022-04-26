/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:44:49 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/12 15:45:05 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sorted(char **env)
{
	int	i;
	int	j;
	int	sorted;

	i = -1;
	sorted = 0;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j])
			if (env[i + 1] && (ft_strcmp(env[i],
						env[i + 1]) > 0))
				sorted = 1;
	}
	return (sorted);
}

void	sorted_env(char ***env)
{
	int		i;
	int		j;
	char	*tmp;

	while (is_sorted(*env))
	{
		i = -1;
		while ((*env)[++i])
		{
			j = -1;
			while ((*env)[i][++j])
			{
				if ((*env)[i + 1] && (ft_strcmp((*env)[i],
						(*env)[i + 1]) > 0))
				{
					tmp = (*env)[i + 1];
					(*env)[i + 1] = (*env)[i];
					(*env)[i] = tmp;
				}
			}
		}
	}
}

int	print_env_sorted(void)
{
	char	**cpy_env;
	char	*new_env;
	int		i;

	i = -1;
	cpy_env = (char **)malloc(sizeof(char *) * (len_array(g_sh.env) + 1));
	if (!cpy_env)
		return (ft_error_malloc(NULL));
	while (g_sh.env[++i])
		cpy_env[i] = g_sh.env[i];
	cpy_env[i] = NULL;
	sorted_env(&cpy_env);
	i = -1;
	while (g_sh.env[++i])
	{
		new_env = ft_strjoin_with_quote("declare -x ", cpy_env[i]);
		if (!new_env)
			return (ft_error_malloc(NULL));
		write(1, new_env, ft_strlen(new_env));
		write(1, "\n", 1);
		free(new_env);
	}
	free(cpy_env);
	return (0);
}
