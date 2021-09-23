/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:08:28 by sabrugie          #+#    #+#             */
/*   Updated: 2021/09/23 12:10:31 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "utils.h"
# include "sig_func.h"

# define M_QUOTED 1
# define M_D_QUOTED 2
# define M_ESCAPE 4
# define M_ESCAPED 8
# define M_ENV_VAR 16
# define M_QU_START 32
# define M_QU_END 64
# define M_ENVNAME 128
# define M_ENVVAR 256

typedef struct s_line_character
{
	char	c;
	uint8_t	flag;
}				t_line_char;

t_line_char		**parse(char *line);

char			**line_split(char **res, t_line_char *s, char c);
t_line_char		**marked_split(t_line_char ***res, t_line_char *s, char c);
size_t			count(t_line_char *s, char c);

char			*lcndup(t_line_char *s, int n);

#endif
