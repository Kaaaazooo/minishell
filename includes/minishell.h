#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/errno.h>
#include <sys/wait.h>

#include "libft.h"

# define M_QUOTED 1
# define M_D_QUOTED 2
# define M_ESCAPE 4
# define M_ESCAPED 8
# define M_ENV_VAR 16
# define M_QU_START 32
# define M_QU_END 64
# define M_ENVNAME 128
# define M_ENVVAR 256

typedef struct	s_line_char
{
	char		c;
	uint16_t	flag;
}		t_line_char;

typedef struct	s_word_desc
{
	char	*word;
	int	flags;
}		t_w_desc;

typedef struct	s_quote_addresses
{
	char				*start;
	char				*end;
	struct s_quote_addresses	*next;
}		t_quotes;

typedef struct	s_command_list
{
	struct s_command_list	*next;
	char			cmd[255];
	int			ac;
	char			**args;
}		t_cmd_lst;

typedef struct	s_bash
{
	char	**env;
}		t_bash;

int		echo(char *str);
int		ft_cd(char *path);
int		ft_pwd(void);

int		char_in_str(char c, char *str);
char		**line_split(t_line_char *s, char c);
char		*lcndup(t_line_char *s, int n);

t_line_char	**marked_split(t_line_char *s, char c);

int		skip_quoted(char *str);

void		mark_env(t_line_char **marked);

t_line_char	**parse(char **line);

char		*lcs_to_strs(t_line_char *marked);

#endif
