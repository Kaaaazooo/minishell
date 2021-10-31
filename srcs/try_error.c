/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:07:59 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/06 17:18:33 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	try_exec(char *path, char *file, char **cmd, char **env)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd >= 0 && !close(fd))
	{
		if (execve(file, cmd, env) < 0)
		{
			if (errno == ENOEXEC || errno == EACCES)
				minishell_error("minishell", strerror(errno), *cmd);
			else
				perror("minishell");
			exit((int)(uint8_t)errno);
		}
	}
	if (fd < 0 && path == NULL)
	{
		printf("errno = %d\n", errno);
		minishell_error("minishell", file, strerror(errno));
		exit(127);
	}
	return (0);
}

int	cmd_not_found(char *str)
{
	minishell_error(str, "command not found", NULL);
	exit(127);
}
