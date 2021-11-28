/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:14:36 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/28 13:10:12 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_buf(char **buf)
{
	t_m_char	*m_str;
	size_t		i;

	m_str = str_to_m_str(*buf);
	if (m_str == NULL)
		return (-1);
	i = 0;
	while (m_str[i].c)
	{
		if (m_str[i++].c == '$')
		{
			if (expand(&m_str, &i))
			{
				free(m_str);
				return (-1);
			}
		}
	}
	free(*buf);
	*buf = m_str_to_str(m_str);
	free(m_str);
	if (buf == NULL)
		return (-1);
	return (0);
}

int	write_heredoc(int fd, char *word)
{
	char	*buf;
	ssize_t	ret;

	buf = readline("> ");
	while (buf && ft_strcmp(buf, word))
	{
		ret = expand_buf(&buf);
		if (!ret)
		{
			ret = write(fd, buf, ft_strlen(buf));
			ret *= write(fd, "\n", 1);
		}
		free(buf);
		if (ret < 0)
		{
			perror("minishell");
			free(buf);
			return (ret);
		}
		buf = readline("> ");
	}
	free(buf);
	return (0);
}

int	clear_heredocs(t_cmd *cmd)
{
	size_t	i;
	size_t	j;
	char	filename[256];

	i = SIZE_MAX;
	while (cmd[++i].redir)
	{
		j = SIZE_MAX;
		while (cmd[i].redir[++j])
		{
			ft_memset(filename, 0, 256 * sizeof(char));
			if (!ft_strncmp("<<", cmd[i].redir[j], 2))
			{
				if (unlink(get_heredoc_name(filename, i, ++j))
					&& errno != ENOENT)
				{
					return (-1);
				}
			}
		}
	}
	return (0);
}

int	create_tmp(t_cmd *cmd, size_t i, size_t j)
{
	int		fd;
	char	filename[256];

	get_heredoc_name(filename, i, j);
	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (-1);
	if (write_heredoc(fd, cmd[i].redir[j]))
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	heredoc(t_cmd *cmd)
{
	size_t	i;
	size_t	j;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	g_sh.pipe = 1;
	if (pid == 0)
	{
		signal(SIGINT, sig_heredoc);
		i = SIZE_MAX;
		while (cmd[++i].redir)
		{
			j = SIZE_MAX;
			while (cmd[i].redir[++j])
				if (!ft_strncmp("<<", cmd[i].redir[j], 2))
					if (create_tmp(cmd, i, ++j))
						exit (errno + 128);
		}
		exit(0);
	}
	return (wait_heredoc(pid));
}
