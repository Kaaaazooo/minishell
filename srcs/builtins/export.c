/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moakouda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:59:22 by moakouda          #+#    #+#             */
/*   Updated: 2021/11/28 18:14:40 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update(const char *content, int index)
{
	char	*new_env;

	new_env = NULL;
	if (ft_strchr(content, '='))
	{
		new_env = ft_strdup(content);
		if (!new_env)
			return (ft_error_malloc());
		free(g_sh.env[index]);
		g_sh.env[index] = new_env;
	}
	return (0);
}

int	ft_set_variable(const char *argv)
{
	char	**new_env;
	int		i;
	char	*pwd;

	i = -1;
	pwd = NULL;
	new_env = (char **)ft_calloc(sizeof(char *), (len_array(g_sh.env) + 2));
	if (!new_env)
		return (ft_error_malloc());
	while (g_sh.env[++i])
	{
		new_env[i] = ft_strdup(g_sh.env[i]);
		if (!new_env[i])
			return (ft_free_tab_malloc(new_env, i));
	}
	if (!ft_strcmp(argv, "PWD"))
		new_env[i] = ft_strjoin("PWD=", getcwd(pwd, 32768));
	else
		new_env[i] = ft_strdup(argv);
	free(pwd);
	if (!new_env[i])
		return (ft_free_tab_malloc(new_env, i));
	free_strs(g_sh.env, i);
	g_sh.env = new_env;
	return (0);
}

int	ft_do_export(char *tmp, const char *argv, int i)
{
	int	j;
	int	len_tmp;

	len_tmp = ft_strlen(tmp);
	while (g_sh.env[++i])
	{
		j = 0;
		while (g_sh.env[i][j] != '\0' && g_sh.env[i][j] != '=')
			j++;
		if (len_tmp > j)
			j = len_tmp;
		if (len_tmp && !ft_strncmp(tmp, g_sh.env[i], j))
		{
			free(tmp);
			return (ft_update(argv, i));
		}
		else if (!g_sh.env[i + 1])
		{
			free(tmp);
			return (ft_set_variable(argv));
		}
	}
	return (0);
}

int	ft_before_export(const char *argv, int *not_valid)
{
	char	*tmp;
	int		i;

	i = 0;
	while (argv[i] != '\0' && argv[i] != '=')
		i++;
	tmp = (char *)ft_calloc(sizeof(char), (i + 1));
	if (!tmp)
		return (ft_error_malloc());
	tmp = ft_strncpy(tmp, argv, i);
	i = -1;
	if (check_argv(tmp) || !ft_strcmp(tmp, ""))
	{
		write(2, "minishell: export: `", 20);
		write(2, argv, ft_strlen((char *)argv));
		minishell_error("'", "not a valid identifier", NULL);
		*not_valid = 1;
		free(tmp);
	}
	else
	{
		if (ft_do_export(tmp, argv, i))
			return (1);
	}
	return (0);
}

int	ft_export(const char **argv)
{
	int	cmd;
	int	not_valid;

	cmd = 0;
	not_valid = 0;
	if (!argv[1])
	{
		if (print_env_sorted())
			return (1);
	}
	else
		while (argv[++cmd])
			if (ft_before_export(argv[cmd], &not_valid))
				return (1);
	return (not_valid);
}
