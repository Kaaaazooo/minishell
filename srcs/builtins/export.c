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

int	ft_update(const char *content, int index, int concatenate)
{
	char	*new_env;

	new_env = NULL;
	if (ft_strchr(content, '='))
	{
		if (concatenate)
			new_env = ft_strjoin(g_sh.env[index], &content[concatenate + 1]);
		else
			new_env = ft_strdup(content);
		if (!new_env)
			return (ft_error_malloc((char *)content));
		free(g_sh.env[index]);
		g_sh.env[index] = new_env;
	}
	free((void *)content);
	return (0);
}

int	ft_set_variable(const char *argv)
{
	char	**new_env;
	int		i;

	i = -1;
	new_env = (char **)ft_calloc(sizeof(char *), (len_array(g_sh.env) + 2));
	if (!new_env)
		return (ft_error_malloc((void *)argv));
	while (g_sh.env[++i])
	{
		new_env[i] = ft_strdup(g_sh.env[i]);
		if (!new_env[i])
			return (ft_free_tab_malloc(new_env, i, argv));
	}
	new_env[i] = ft_strdup(argv);
	if (!new_env[i])
		return (ft_free_tab_malloc(new_env, i, argv));
	free_strs(g_sh.env, i);
	g_sh.env = new_env;
	free((void *)argv);
	return (0);
}

int	ft_do_export(char *tmp, const char *argv, int i)
{
	int			j;
	int			len_tmp;
	const char	*new_argv;
	int			concatenate;

	concatenate = 0;
	new_argv = ft_concatenate(argv, &concatenate, &tmp);
	if (!new_argv)
		return (ft_error_malloc(NULL));
	len_tmp = ft_strlen(tmp);
	while (g_sh.env[++i])
	{
		j = 0;
		while (g_sh.env[i][j] != '\0' && g_sh.env[i][j] != '=')
			j++;
		if (len_tmp > j)
			j = len_tmp;
		if (len_tmp && !ft_strncmp(tmp, g_sh.env[i], j))
			return (ft_update(new_argv, i, concatenate));
		else if (!g_sh.env[i + 1])
			return (ft_set_variable(new_argv));
	}
	free((void *)new_argv);
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
		return (ft_error_malloc(NULL));
	tmp = ft_strncpy(tmp, argv, i);
	i = -1;
	if (check_argv((char *)argv, 1) || !ft_strcmp(tmp, ""))
		not_valid_identifier(argv, not_valid);
	else
	{
		if (ft_do_export(tmp, argv, i))
		{
			free(tmp);
			return (1);
		}
	}
	free(tmp);
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
