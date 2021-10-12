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

int	main(void)
{
	char		*buf;

	while (1)
	{
		buf = readline("minishell$ ");
		if (buf == NULL)
			break ;
		printf("cmd = [%s]\n", buf);
		if (ft_strlen(buf) == 0)
		{
			free(buf);
			continue ;
		}
		add_history(buf);
		if (!strcmp(buf, "exit"))
			break ;
		parse(buf);
		free(buf);
	}
	free(buf);
	return (0);
}
//	t_line_char	*marked;
//	system("leaks minishell");
//	signal(SIGINT, SIG_IGN);
//		marked = parse(buf);
//		for (int i = 0; marked[i].c; i++)
//			printf("marked[%d] = [%c] | %d\n", i, marked[i].c, marked[i].flag);
//		free(marked);
