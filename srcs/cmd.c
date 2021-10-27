/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:07:59 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/06 17:18:33 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	alloc_cmd(t_cmd *cmd, t_token *token)
{
	size_t	n[2];

	ft_memset(n, 0, sizeof(size_t) * 2);
	while (token->str && !(token->flag && *(token->str) == '|'))
		n[token++->flag] += 1;
	cmd->av = ft_calloc(n[0] + 1, sizeof(char *));
	cmd->redir = ft_calloc(n[1] + 1, sizeof(char *));
	if (cmd->av == NULL || cmd->redir == NULL)
	{
		free_strs(cmd->av, n[0]);
		free_strs(cmd->redir, n[1]);
		return (-1);
	}
	return (0);
}

int	get_cmd_tab(t_cmd **cmd, t_token *token, size_t size)
{
	size_t	i;
	size_t	n[2];

	i = 0;
	*cmd = ft_calloc(size + 1, sizeof(t_cmd));
	if (*cmd == NULL)
		return (-1);
	while (token->str)
	{
		if (alloc_cmd(&((*cmd)[i]), token))
			return (-1);
		ft_memset(n, 0, sizeof(size_t) * 2);
		while (token->str && !(token->flag && *(token->str) == '|'))
		{
			if (token->flag)
				(*cmd)[i].redir[(n[0])++] = token->str;
			else
				(*cmd)[i].av[(n[1])++] = token->str;
			++token;
		}
		if (token->str)
			++token;
		++i;
	}
	return (0);
}

void	print_cmd(t_cmd *cmd)
{
	for (int i = 0; cmd[i].av; i++)
	{
		printf("ARGS:\n");
		for (int j = 0; cmd[i].av[j]; j++)
			printf("[%s]\n", cmd[i].av[j]);
		printf("\nREDIR:\n");
		for (int j = 0; cmd[i].redir[j]; j++)
			printf("[%s]\n", cmd[i].redir[j]);
		printf("______________\n\n");
	}
}

////////////

void	minishell_error(char *error, char *arg)
{
	int		i;
	char	buf[8096];

	i = 0;
	while (i < 8096)
		buf[i++] = 0;
	ft_strcpy(buf + ft_strlen(buf), "minishell: ");
	ft_strcpy(buf + ft_strlen(buf), error);
	ft_strcpy(buf + ft_strlen(buf), ": ");
	if (arg)
		ft_strcpy(buf + ft_strlen(buf), arg);
	ft_strcpy(buf + ft_strlen(buf), "\n");
	write(STDERR_FILENO, buf, ft_strlen(buf));
}

int	try_exec(char *file, char **cmd, char **env)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd >= 0 && !close(fd))
	{
		if (execve(file, cmd, env) < 0)
		{
			if (errno == ENOEXEC || errno == EACCES)
				minishell_error(strerror(errno), *cmd);
			else
				perror("minishell");
			exit(errno);
		}
	}
	return (0);
}

int	cmd_not_found(char *str)
{
	minishell_error("command not found", str);
	exit(127);
}

char	*joinpath_to_file(char *path, char *filename)
{
	char	*file;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (tmp == NULL)
		return (NULL);
	file = ft_strjoin(tmp, filename);
	free(tmp);
	if (file == NULL)
		return (NULL);
	return (file);
}

void	redir(t_cmd cmd)
{
	size_t	i;
	int		fd;

	i = SIZE_MAX;
	while (cmd.redir[++i])
	{
		if (!ft_strncmp(">>", cmd.redir[i], 2))
		{
			fd = open(cmd.redir[++i], O_RDWR | O_TRUNC | O_CREAT | O_APPEND,
					0644);
			if (fd < 0)
			{
				minishell_error(cmd.redir[i], strerror(errno));
				exit(errno + 127);
			}
			dup2(fd, 1);
		}
		else if (!ft_strncmp("<<", cmd.redir[i], 2))
		{
			printf("STDIN REDIR WHILE NOT %s\n", cmd.redir[++i]);
		}
		else if (cmd.redir[i][0] == '>')
		{
			fd = open(cmd.redir[++i], O_RDWR | O_TRUNC | O_CREAT, 0644);
			if (fd < 0)
			{
				minishell_error(cmd.redir[i], strerror(errno));
				exit(errno + 127);
			}
			dup2(fd, 1);
		}
		else if (cmd.redir[i][0] == '<')
		{
			fd = open(cmd.redir[++i], O_RDONLY);
			if (fd < 0)
			{
				minishell_error(cmd.redir[i], strerror(errno));
				exit(errno + 127);
			}
			dup2(fd, 0);
		}
	}
}

int	exec_cmd(t_cmd cmd, char **env)
{
	char	*tmp;
	char	**paths;
	size_t	i;

	redir(cmd);
	paths = ft_split(getenv("PATH"), ':');
	if (paths == NULL)
		exit(1);
	i = SIZE_MAX;
	while (paths[++i])
	{
		tmp = joinpath_to_file(paths[i], *(cmd.av));
		if (tmp == NULL || try_exec(tmp, cmd.av, env))
			exit(errno + 127);
		free(tmp);
	}
	if (!paths[i])
		cmd_not_found(*(cmd.av));
	free_strs(paths, i);
	exit(errno);
}

int	cmd(t_token *token, char **env)
{
	size_t	n;
	t_token	*tmp;
	t_cmd	*cmd;

	n = SIZE_MAX;
	while (token[++n].str)
	{
		if (token[n].flag && *(token[n].str) != '|')
		{
			if (token[n + 1].str && !token[n + 1].flag)
				token[n++ + 1].flag = 1;
			else
				printf("syntax error\n");
		}
	}
	n = 1;
	tmp = token;
	while (tmp->str)
		if (*(tmp++->str) == '|')
			n += (tmp - 1)->flag;
	if (get_cmd_tab(&cmd, token, n))
		printf("MALLOC FAILED\n");
	pipeline(token, cmd, n, env);
	return (0);
}
