/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:14:47 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/12 18:21:09 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mark_redir(t_token **token)
{
	size_t	n;

	n = SIZE_MAX;
	while ((*token)[++n].str)
	{
		if ((*token)[n].flag && *((*token)[n].str) != '|')
		{
			if ((*token)[n + 1].str && !(*token)[n + 1].flag)
				(*token)[n++ + 1].flag = 1;
			else
			{
				minishell_error("minishell",
					"syntax error near unexpected token", NULL);
				return (-1);
			}
		}
		else if ((*token)[n].flag && (*token)[n + 1].str == NULL)
		{
			minishell_error("minishell",
				"syntax error near unexpected token", NULL);
			return (-1);
		}
	}
	return (0);
}
