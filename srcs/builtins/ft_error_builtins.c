/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moakouda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 22:25:53 by moakouda          #+#    #+#             */
/*   Updated: 2021/11/28 12:55:58 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_malloc(char *str)
{
	if (*str)
		free(str);
	perror("minishell");
	return (1);
}

int	ft_free_tab_malloc(char **new_env, int i, const char *argv)
{
	free_strs(new_env, i);
	(void)argv;
	free((void *)argv);
	return (ft_error_malloc(NULL));
}

void	not_valid_identifier(const char *argv, int *not_valid)
{
	write(2, "minishell: export: `", 20);
	write(2, argv, ft_strlen((char *)argv));
	minishell_error("'", "not a valid identifier", NULL);
	*not_valid = 1;
}

const char	*ft_concatenate(const char *argv, int *concatenate, char **tmp)
{
	char	*new_argv;
	int		i;

	i = -1;
	if (ft_strstr(argv, "+="))
	{
		new_argv = (char *)ft_calloc(sizeof(char), ft_strlen((char *)argv) + 1);
		if (!new_argv)
			return (NULL);
		while (argv[++i] != '+')
			new_argv[i] = argv[i];
		*concatenate = i;
		(*tmp)[i] = '\0';
		while (argv[i++] != '\0')
			new_argv[i - 1] = argv[i];
		new_argv[i - 1] = '\0';
	}
	else
		new_argv = ft_strdup(argv);
	return (new_argv);
}
