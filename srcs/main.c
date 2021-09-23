/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:07:59 by sabrugie          #+#    #+#             */
/*   Updated: 2021/09/23 13:15:39 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*buf;
	t_line_char	**marked;	

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
		marked = parse(buf);
		for (int i = 0; marked[i]; i++)
			free(marked[i]);
		free(marked);
		free(buf);
	}
	return (0);
}
/*		for (int j = 0; marked[i][j].c; j++)
**			printf("marked[%d][%d].c = [%c] | %d\n",
**				i, j, marked[i][j].c, marked[i][j].flag);
**		printf("\n");
*/
//	signal(SIGINT, SIG_IGN);
