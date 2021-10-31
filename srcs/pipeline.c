/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:07:59 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/06 17:18:33 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_pipes(int *p, size_t n)
{
	size_t	i;

	i = 0;
	while (i < (n - 1) * 2)
		close(p[i++]);
	return (0);
}

void	dup_fd(t_cmd *cmd, size_t i, size_t n, int *p)
{
	signal(SIGQUIT, SIG_DFL);
	if (i)
		dup2(p[(i - 1)*2], 0);
	if (cmd[i + 1].av || cmd[i + 1].av)
		dup2(p[i * 2 + 1], 1);
	close_pipes(p, n);
}

int	pipe_loop(t_cmd *cmd, int *p, pid_t *pid, char **env)
{
	size_t	i;
	size_t	n;

	n = 0;
	while (cmd[n].av || cmd[n].redir)
		++n;
	i = SIZE_MAX;
	while (++i < n)
	{
		pid[i] = fork();
		g_sh.pid = pid[i];
		g_sh.pipe = 1;
		if (pid[i] < 0)
			return (-1);
		if (!pid[i])
		{
			dup_fd(cmd, i, n, p);
			if (cmd[i].av[0])
				exec_cmd(cmd[i], env);
			exit(errno + 127);
		}
	}
	return (0);
}

void	free_pipeline(t_token *token, t_cmd *cmd, int *p, pid_t *pid)
{
	size_t	i;

	i = 0;
	while (cmd[i].av || cmd[i].redir)
	{
		free(cmd[i].av);
		free(cmd[i++].redir);
	}
	i = 0;
	while (token[i].str)
		free(token[i++].str);
	free(token);
	free(cmd);
	free(p);
	free(pid);
}

int	pipeline(t_token *token, t_cmd *cmd, size_t n, char **env)
{
	size_t	i;
	int		*p;
	pid_t	*pid;

	p = malloc((n - 1) * 2 * sizeof(int));
	if (p == NULL)
		return (-1);
	pid = malloc(n * sizeof(pid_t));
	if (pid == NULL)
	{
		free(p);
		return (-1);
	}
	i = 0;
	while (i < (n - 1))
		pipe(&p[i++ *2]);
	pipe_loop(cmd, p, pid, env);
	close_pipes(p, n);
	wait_process(n, pid);
	free_pipeline(token, cmd, p, pid);
	return (0);
}
