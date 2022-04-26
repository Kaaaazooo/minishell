/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moakouda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:58:32 by moakouda          #+#    #+#             */
/*   Updated: 2021/11/28 12:56:37 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_content_pwd(void)
{
	int		index;
	int		i;
	char	*pwd;
	char	*content;

	i = 0;
	index = find_pwd(g_sh.env);
	pwd = (char *)malloc(sizeof(char) * ft_strlen(g_sh.env[index]) + 1);
	if (!pwd)
		return (NULL);
	while (g_sh.env[index][i] != '=')
		i++;
	content = pwd;
	if (g_sh.env[index][i] == '=')
	{
		while (g_sh.env[index][++i])
			*pwd++ = g_sh.env[index][i];
		*pwd = '\0';
	}
	else
		pwd = "";
	return (content);
}

int	check_oldpwd(void)
{
	int		i;
	char	*tmp;
	char	*pwd;

	i = -1;
	tmp = NULL;
	pwd = NULL;
	while (g_sh.env[++i])
	{
		if (!ft_strncmp(g_sh.env[i], "OLDPWD", 6))
		{
			pwd = get_content_pwd();
			if (!pwd)
				return (ft_error_malloc(NULL));
			tmp = ft_strjoin("OLDPWD=", pwd);
			free(pwd);
			if (!tmp)
				return (ft_error_malloc(NULL));
			free(g_sh.env[i]);
			g_sh.env[i] = tmp;
			return (0);
		}
	}
	return (0);
}

int	update_pwd(void)
{
	int		i;
	char	*tmp;
	char	*pwd;

	tmp = NULL;
	pwd = NULL;
	i = find_pwd(g_sh.env);
	if (i >= 0)
	{
		pwd = getcwd(tmp, 32768);
		if (!pwd)
			return (ft_error_malloc(NULL));
		tmp = ft_strjoin("PWD=", pwd);
		free(pwd);
		if (!tmp)
			return (ft_error_malloc(NULL));
		free(g_sh.env[i]);
		g_sh.env[i] = tmp;
	}
	return (0);
}

int	reset_oldpwd(void)
{
	int		i;
	char	*new_env;

	i = 0;
	new_env = NULL;
	while (g_sh.env[i] && ft_strncmp(g_sh.env[i], "OLDPWD=", 7))
		i++;
	if (!g_sh.env[i])
		return (0);
	new_env = ft_strdup("OLDPWD=");
	if (!new_env)
		return (ft_error_malloc(NULL));
	free(g_sh.env[i]);
	g_sh.env[i] = new_env;
	return (0);
}

int	ft_cd(const char **argv)
{
	if (find_pwd(g_sh.env) >= 0)
	{
		if (check_oldpwd())
			return (1);
	}
	else
		if (reset_oldpwd())
			return (1);
	if (argv[1] == NULL)
	{
		if (chdir(ft_getenv("HOME")) < 0)
		{
			minishell_error("minishell", "cd", "HOME not set");
			return (1);
		}
	}
	else if (chdir(argv[1]) < 0)
	{
		minishell_error("minishell: cd", (char *)argv[1], strerror(errno));
		return (1);
	}
	if (update_pwd())
		return (1);
	return (0);
}
