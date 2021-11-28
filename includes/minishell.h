/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:08:28 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/28 13:06:43 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "utils.h"

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

typedef struct s_shell
{
	pid_t	pid;
	uint8_t	pipe;
	int		status;
	char	**env;
}		t_sh;

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

int			set_new_shlvl(int lvl);
int			get_shlvl(char *shlvl);
void		shltermios(int ac, char **av, struct termios *t);

t_token		*parse(char *line);
char		**split_word(char ***dst, char *s);
uint32_t	count_words(char *buf);
int			mark_redir(t_token **token);
char		*quoted(char *buf, char **end_quote);
int			quote_is_closed(char *word);
uint8_t		is_metachar(char *str);
int			expansion(t_token *token, t_m_char **m_str, uint8_t metachar);
int			expand(t_m_char **m_str, size_t *i);
int			merge_env(t_m_char **m_str, char *env_var, size_t *i, size_t j);
char		*m_str_to_str(t_m_char *m_str);
t_m_char	*str_to_m_str(char *str);
size_t		m_strlen(t_m_char *m_str);

char		**free_strs(char **strs, int j);

int			cmd(t_token *token);
int			exec_cmd(t_cmd cmd);
int			pipeline(t_token *token, t_cmd *cmd, size_t n);
int			free_pipeline(t_token *token, t_cmd *cmd, int *p, pid_t *pid);
void		minishell_error(char *s1, char *s2, char *s3);

int			close_pipes(int *p, size_t n);
void		dup_fd(t_cmd *cmd, size_t i, size_t n, int *p);

int			handle_redir(t_cmd cmd, size_t i);
int			redir(int dst, char *file, int flags, mode_t mode);

int			heredoc(t_cmd *cmd);
char		*get_heredoc_name(char *dst, size_t i, size_t j);
int			clear_heredocs(t_cmd *cmd);
int			wait_heredoc(pid_t pid);
void		sig_heredoc(int signo);
char		*get_heredoc_name(char *dst, size_t i, size_t j);

int			cmd_not_found(char *str);
int			try_exec(char *path, char *file, char **cmd);
int			try_builtin(t_cmd cmd);
void		wait_process(size_t n, pid_t *pid);
int			is_path(char *str);

void		sigint(int signo);
void		sighandler(int signe);

char		*ft_getenv(char *name);
char		**alloc_env(char **env);
int			ft_putenv(char *string);

int			ft_cd(const char **argv);
int			ft_echo(const char **argv);
int			ft_env(const char **argv);
void		ft_exit(const char **argv);
int			ft_export(const char **argv);
int			ft_pwd(const char **argv);
int			ft_unset(const char **argv);
int			ft_error_malloc(void);
int			ft_free_tab_malloc(char **new_env, int i);
int			print_env_sorted(void);

extern t_sh	g_sh;

#endif
