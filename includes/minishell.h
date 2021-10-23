/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:08:28 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/12 17:02:29 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "utils.h"
# include "sig_func.h"

# define BLANK 1
# define GREAT 2
# define G_GREAT 4
# define LESS 8
# define L_LESS 16
# define PIPE 32

# define M_QU_START 1
# define M_QU_END 2
# define M_QUOTED 4
# define M_D_QUOTED 8

typedef struct s_token
{
	char	*str;
	uint8_t	flag;
}		t_token;

typedef struct s_command
{
	char	**av;
	char	**redir;
}		t_cmd;

typedef struct s_marked_char
{
	char	c;
	uint8_t	flag;
}		t_m_char;

t_token		*parse(char *line);
char		**split_word(char ***dst, char *s);
uint32_t	count_words(char *buf);
char		*quoted(char *buf, char **end_quote);
uint8_t		is_metachar(char *str);
int			expansion(t_token *token, t_m_char **m_str, uint8_t metachar);
char		*m_str_to_str(t_m_char *m_str);

char		**free_strs(char **strs, int j);

#endif
