/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 19:57:24 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/27 19:58:41 by sabrugie         ###   ########.fr       */
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
		dup2(p[(i - 1) *2], 0);
	if (cmd[i + 1].av || cmd[i + 1].av)
		dup2(p[i * 2 + 1], 1);
	close_pipes(p, n);
}
