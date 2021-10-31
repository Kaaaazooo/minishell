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

int	exec_cmd(t_cmd cmd, char **env)
{
	char	*tmp;
	char	**paths;
	size_t	i;

	handle_redir(cmd);
	paths = ft_split(getenv("PATH"), ':');
	if (paths == NULL)
		exit(1);
	if (try_exec(*paths, cmd.av[0], cmd.av, env))
		exit(errno + 127);
	i = SIZE_MAX;
	while (paths[++i])
	{
		tmp = joinpath_to_file(paths[i], *(cmd.av));
		if (tmp == NULL || try_exec(paths[i], tmp, cmd.av, env))
			exit((int)(uint8_t)(errno + 127));
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
	//printf("$? = [%s]\n", getenv("?"));
