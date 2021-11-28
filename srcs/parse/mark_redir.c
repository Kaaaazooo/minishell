/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:14:47 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/28 19:53:10 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unexpected_token(char *str)
{
	char	msg[128];

	ft_strcpy(msg, "syntax error near unexpected token '");
	if (str)
		ft_strcpy(msg + ft_strlen(msg), str);
	else
		ft_strcpy(msg + ft_strlen(msg), "newline");
	ft_strcpy(msg + ft_strlen(msg), "'");
	minishell_error("minishell", msg, NULL);
}

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
				unexpected_token((*token)[n + 1].str);
				return (-1);
			}
		}
		else if ((*token)[n].flag && ((*token)[n + 1].str == NULL
			|| is_metachar((*token)[n + 1].str) == PIPE))
		{
			unexpected_token((*token)[n + 1].str);
			return (-1);
		}
	}
	return (0);
}
