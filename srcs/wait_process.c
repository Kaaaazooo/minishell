/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:07:59 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/06 17:18:33 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_process(size_t n, pid_t *pid)
{
	size_t	i;
	int		status;

	i = 0;
	status = 0;
	while (i < n)
	{
		waitpid(pid[i++], &status, 0);
		if (WIFSIGNALED(status))
			if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
	}
	g_sh.pipe = 0;
	if (WIFEXITED(status))
		g_sh.status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		g_sh.status = 128 + WTERMSIG(status);
	}
}
