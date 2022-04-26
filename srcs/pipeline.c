/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:07:59 by sabrugie          #+#    #+#             */
/*   Updated: 2021/12/01 19:06:46 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_loop(t_cmd *cmd, int *p, pid_t *pid)
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
			if (handle_redir(cmd[i], i))
				exit(errno + 128);
			if (cmd[i].av[0] || cmd[i].redir[0])
				exec_cmd(cmd[i]);
			exit(errno + 128);
		}
	}
	return (0);
}

int	free_pipeline(t_token *token, t_cmd *cmd, int *p, pid_t *pid)
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
	token = NULL;
	free(cmd);
	cmd = NULL;
	free(p);
	free(pid);
	return (0);
}

int	no_pipe_builtin(t_token *token, t_cmd *cmd)
{
	int	s[2];

	if (cmd->av[0] == NULL
		|| (ft_strcmp("cd", cmd->av[0]) && ft_strcmp("echo", cmd->av[0])
			&& ft_strcmp("env", cmd->av[0]) && ft_strcmp("exit", cmd->av[0])
			&& ft_strcmp("export", cmd->av[0]) && ft_strcmp("pwd", cmd->av[0])
			&& ft_strcmp("unset", cmd->av[0])))
		return (0);
	s[0] = dup(0);
	s[1] = dup(1);
	if (handle_redir(*cmd, 0) == 0)
		try_builtin(*cmd);
	close(0);
	close(1);
	dup2(s[0], 0);
	dup2(s[1], 1);
	close(s[0]);
	close(s[1]);
	clear_heredocs(cmd);
	free_pipeline(token, cmd, NULL, NULL);
	return (1);
}

int	pipeline(t_token *token, t_cmd *cmd, size_t n)
{
	size_t	i;
	int		*p;
	pid_t	*pid;

	if (n == 1 && no_pipe_builtin(token, cmd))
		return (0);
	p = malloc((n) * 2 * sizeof(int));
	pid = ft_calloc(n, sizeof(pid_t));
	if (p == NULL || pid == NULL)
	{
		free(p);
		free(pid);
		return (-1);
	}
	i = 0;
	while (i < (n - 1))
		pipe(&p[i++ *2]);
	pipe_loop(cmd, p, pid);
	close_pipes(p, n);
	wait_process(n, pid);
	clear_heredocs(cmd);
	return (free_pipeline(token, cmd, p, pid));
}
