/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:09:13 by sabrugie          #+#    #+#             */
/*   Updated: 2021/09/29 18:52:23 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_token(t_line_char *marked)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (marked[i].c)
	{
		while (marked[i].c && marked[i].flag & M_CONTROL)
			++i;
		++j;
		++i;
	}
}

void	trim_redir(t_line_char **marked)
{
	int			i;
	int			j;
	int			k;
	t_line_char	*new;

	i = 0;
	while (marked[i])
	{
		j = 0;
		k = 0;
		while (marked[i][j].c)
			if (marked[i][j++].flag ^  M_CONTROL)
				++k;
		new = ft_calloc(k + 1, sizeof(t_line_char));
		j = 0;
		k = 0;
		while (marked[i][j].c)
		{
			while (marked[i][j].flag &  M_CONTROL)
				++j;
			new[k].c = marked[i][j].c;
			new[k++].flag = marked[i][j++].flag;
		}
		printf("av\n");
		free(marked[i]);
		printf("ap\n");
		marked[i] = new;
		++i;
	}
}
