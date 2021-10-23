/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:07:59 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/06 17:18:33 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_args(char ***av, t_token *token, t_token **last_token, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ft_memset(*av, 0, sizeof(char *) * (n + 1));
	while (token[i].str)
	{
		if (token[i].flag == 0)
			(*av)[j++] = token[i++].str;
		if (token[i].flag && *(token[i].str) != '|' && token[i + 1].str)
		{
			if (token[i + 1].flag == 0)
				++i;
			else
				return (-1);
			++i;
		}
		else if (token[i].flag && token[i + 1].str == NULL)
			return (-1);
		else if (token[i].flag && *(token[i++].str) == '|')
			break ;
	}
	*last_token = &token[i];
	return (!(token[i].str));
}

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

int	cmd(t_token *token, char **env)
{
	size_t	n;
	t_token	*tmp;
	t_cmd	*cmd;

	(void)env;
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
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char		*buf;
	t_token		*token;

	(void)ac;
	(void)av;
	while (1)
	{
		buf = readline("minishell$ ");
		if (buf == NULL)
			break ;
		if (ft_strlen(buf) == 0)
		{
			free(buf);
			continue ;
		}
		add_history(buf);
		token = parse(buf);
		cmd(token, env);
		free(token);
		if (!strcmp(buf, "exit"))
			break ;
		free(buf);
	}
	free(buf);
	return (0);
}
