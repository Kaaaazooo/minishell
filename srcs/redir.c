/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:07:59 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/28 03:05:54 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(int dst, char *file, int flags, mode_t mode)
{
	int	fd;
	int	error;

	fd = open(file, flags, mode);
	if (fd < 0)
	{
		error = errno;
		minishell_error("minishell", file, strerror(errno));
		errno = error;
		return (errno);
	}
	if (dup2(fd, dst) < 0)
	{
		error = errno;
		minishell_error("minishell", file, strerror(errno));
		errno = error;
		return (errno);
	}
	return (0);
}

int	handle_redir(t_cmd cmd, size_t i)
{
	size_t	j;
	char	filename[256];

	j = SIZE_MAX;
	while (cmd.redir[++j])
	{
		if (!ft_strncmp(">>", cmd.redir[j], 2) && redir(1, cmd.redir[++j],
				O_WRONLY | O_CREAT | O_APPEND, 0644))
			return (errno);
		else if (!ft_strncmp("<<", cmd.redir[j], 2)
			&& redir(0, get_heredoc_name(filename, i, ++j), O_RDONLY, 0))
			return (errno);
		else if (cmd.redir[j][0] == '>' && redir(1, cmd.redir[++j],
			O_WRONLY | O_TRUNC | O_CREAT, 0644))
			return (errno);
		else if (cmd.redir[j][0] == '<' && redir(0, cmd.redir[++j],
			O_RDONLY, 0))
			return (errno);
	}
	return (0);
}
