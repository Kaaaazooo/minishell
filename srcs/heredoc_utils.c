/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:46:38 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/23 16:48:31 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_heredoc_name(char *dst, size_t i, size_t j)
{
	ft_memset(dst, 0, 256 * sizeof(char));
	ft_strcpy(dst, ".tmp_");
	ft_llutoa(dst + ft_strlen(dst), (long long unsigned int) i);
	ft_llutoa(dst + ft_strlen(dst), (long long unsigned int) j);
	return (dst);
}

void	sig_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
}
