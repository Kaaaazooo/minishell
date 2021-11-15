/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:07:59 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/06 17:18:33 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir(int dst, char *file, int flags, mode_t mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd < 0)
	{
		minishell_error("minishell1", file, strerror(errno));
		exit(errno + 127);
	}
	if (dup2(fd, dst) < 0)
	{
		minishell_error("minishell2", file, strerror(errno));
		exit(errno + 127);
	}
}

void	heredoc(void)
{
	char	buf[1024];
	ssize_t	ret;

	ret = read(0, buf, 1023);
	buf[ret] = 0;
	while (ret > 0)
	{
		printf("[%s]\n", buf);
		ret = read(0, buf, 1023);
		buf[ret] = 0;
	}
}

void	handle_redir(t_cmd cmd)
{
	size_t	i;

	i = SIZE_MAX;
	while (cmd.redir[++i])
	{
		if (!ft_strncmp(">>", cmd.redir[i], 2))
		{
			redir(1, cmd.redir[++i],
				O_RDWR | O_TRUNC | O_CREAT | O_APPEND, 0644);
		}
		else if (!ft_strncmp("<<", cmd.redir[i], 2))
		{
			printf("STDIN REDIR WHILE NOT %s\n", cmd.redir[++i]);
		}
		else if (cmd.redir[i][0] == '>')
		{
			redir(1, cmd.redir[++i],
				O_RDWR | O_TRUNC | O_CREAT, 0644);
		}
		else if (cmd.redir[i][0] == '<')
			redir(0, cmd.redir[++i], O_RDONLY, 0);
	}
}
