/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:07:59 by sabrugie          #+#    #+#             */
/*   Updated: 2021/12/01 22:48:57 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh	g_sh;

void	ret_error(t_token *token)
{
	size_t	i;

	if (errno)
	{
		perror("minishell");
		g_sh.status = errno + 128;
	}
	else
		g_sh.status = 258;
	i = 0;
	if (token)
		while (token[i].str)
			free(token[i++].str);
	free(token);
}

void	sighandler(int signo)
{
	if (signo == SIGINT && g_sh.pipe == 0)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		g_sh.status = 1;
		write(1, "\n", 1);
		rl_redisplay();
	}
}

void	signals(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}

int	minishell_loop(void)
{
	char		*buf;
	t_token		*token;

	signals();
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
		if (token && token->str == NULL)
			free(token);
		else if (cmd(token))
			ret_error(token);
		free(buf);
	}
	free(buf);
	write(2, "exit\n", 5);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int				i;
	int				error;
	struct termios	t;

	shltermios(ac, av, &t);
	env = alloc_env(env);
	error = 0;
	g_sh.pipe = 0;
	g_sh.status = 0;
	if (env == NULL || get_shlvl(ft_getenv("SHLVL")))
	{
		error = errno;
		perror("minishell");
	}
	else
		minishell_loop();
	i = 0;
	while (g_sh.env && g_sh.env[i])
		free(g_sh.env[i++]);
	free(g_sh.env);
	if (error)
		return (error + 128);
	return (g_sh.status);
}
