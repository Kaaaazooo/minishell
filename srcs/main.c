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
		if (!strcmp(buf, "exit"))
			break ;
		free(buf);
	}
	free(buf);
	return (0);
}
