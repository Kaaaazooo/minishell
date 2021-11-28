/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_is_closed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 15:51:16 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/20 15:51:29 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_is_closed(char *word)
{
	size_t	j;
	char	error[64];

	j = 1;
	while (word[j])
		if (word[j++] == *word)
			return (1);
	ft_memset(error, 0, sizeof(char));
	ft_strcpy(error, "unexpected newline while looking for matching `");
	ft_strlcpy(error + ft_strlen(error), word, 2);
	ft_strcpy(error + ft_strlen(error), "'");
	minishell_error("minishell", error, NULL);
	return (0);
}
