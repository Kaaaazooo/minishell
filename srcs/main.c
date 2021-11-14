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

t_sh	g_sh;

void	sighandler(int signo)
{
	if (signo == SIGINT && g_sh.pipe == 0)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		g_sh.status = 130;
		write(1, "\n", 1);
		rl_redisplay();
	}
}

void	signals(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}

int	minishell_loop(char **env)
{
	char		*buf;
	t_token		*token;

	while (1)
	{
		signals();
		buf = readline("minishell$ ");
		if (buf == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strlen(buf) == 0)
		{
			free(buf);
			continue ;
		}
		add_history(buf);
		token = parse(buf);
		if (token)
			cmd(token, env);
		free(buf);
	}
	free(buf);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_sh.pipe = 0;
	g_sh.status = 0;
	return (minishell_loop(env));
}
