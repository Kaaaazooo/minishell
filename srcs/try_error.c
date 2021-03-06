/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:07:59 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/28 12:23:23 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_path(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		if (str[i++] == '/')
			return (1);
	return (0);
}

void	minishell_error(char *s1, char *s2, char *s3)
{
	int		i;
	char	buf[8096];

	i = 0;
	while (i < 8096)
		buf[i++] = 0;
	if (s1)
		ft_strcpy(buf + ft_strlen(buf), s1);
	if (s2)
	{
		ft_strcpy(buf + ft_strlen(buf), ": ");
		ft_strcpy(buf + ft_strlen(buf), s2);
	}
	if (s3)
	{
		ft_strcpy(buf + ft_strlen(buf), ": ");
		ft_strcpy(buf + ft_strlen(buf), s3);
	}
	ft_strcpy(buf + ft_strlen(buf), "\n");
	write(STDERR_FILENO, buf, ft_strlen(buf));
}

int	try_builtin(t_cmd cmd)
{
	if (cmd.av[0] != NULL)
	{
		if (!ft_strcmp("cd", cmd.av[0]))
			g_sh.status = ft_cd((const char **)cmd.av);
		else if (!ft_strcmp("echo", cmd.av[0]))
			g_sh.status = ft_echo((const char **)cmd.av);
		else if (!ft_strcmp("env", cmd.av[0]))
			g_sh.status = ft_env((const char **)cmd.av);
		else if (!ft_strcmp("exit", cmd.av[0]))
			ft_exit((const char **)cmd.av);
		else if (!ft_strcmp("export", cmd.av[0]))
			g_sh.status = ft_export((const char **)cmd.av);
		else if (!ft_strcmp("pwd", cmd.av[0]))
			g_sh.status = ft_pwd((const char **)cmd.av);
		else if (!ft_strcmp("unset", cmd.av[0]))
			g_sh.status = ft_unset((const char **)cmd.av);
		else
			return (0);
	}
	else
		return (0);
	return (1);
}

int	try_exec(char *path, char *file, char **cmd)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd >= 0 && !close(fd))
	{
		if (execve(file, cmd, g_sh.env) < 0)
		{
			if (errno == ENOEXEC || errno == EACCES)
				minishell_error("minishell", strerror(errno), *cmd);
			else
				perror("minishell");
			exit((int)(uint8_t)errno);
		}
	}
	if (fd < 0 && (*path == 0 || is_path(*cmd)))
	{
		minishell_error("minishell", file, strerror(errno));
		exit(127);
	}
	return (0);
}

int	cmd_not_found(char *str)
{
	minishell_error("minishell", str, "command not found");
	exit(127);
}
