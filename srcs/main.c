/* Compile with: g++ -Wall –Werror -o shell shell.c */

#include "minishell.h"

pid_t pid;

#define READ  0
#define WRITE 1

int	free_strtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i++] = NULL;
	}
	free(tab);
	tab = NULL;
	return (0);
}

void	getcmdpath(t_line_char **args, char **env)
{
	t_line_char	**cmd;
	char		*tmp;
	char		**paths;
	char		**strs;
	int		i;

	tmp = getenv("PATH");
	paths = ft_split(tmp, ':');
	i = 0;
	cmd = marked_split(*args, ' ');
	while (cmd[i])
		++i;
	strs = calloc(sizeof(char *), i + 1);
	i = 0;
	while (cmd[i])
	{
		mark_env(&cmd[i]);
		strs[i] = lcs_to_strs(cmd[i]);
		++i;
	}
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = tmp;
		tmp = ft_strjoin(paths[i], *strs);
		if (execve(tmp, strs, env) != -1)
		{
			free(tmp);
			free_strtab(strs);
			break ;
		}
		free(tmp);
		++i;
	}
	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
	free_strtab(strs);
}

static int command(t_line_char **args, char **env)
{
	int i;
	int j;
	int pd[2];

	i = 0;
	if (!fork())
	{
		j = 0;
		while (args[j])
			++j;
		for( i=0; i < j - 1; i++)
		{
			pipe(pd);
			if (!fork()) {
				dup2(pd[1], 1);
				getcmdpath(&(args[i]), env);
			}
			wait(NULL);
			dup2(pd[0], 0);
			close(pd[1]);
		}
		getcmdpath(&(args[i]), env);
	}
	else
		wait(NULL);
	return (0);
}
//
///* Final cleanup, 'wait' for processes to terminate.
// *  n : Number of times 'command' was invoked.
// */
//void cleanup(int n)
//{
//	int i;
//	for (i = 0; i < n; ++i)
//		wait(NULL);
//}
//
//static int n = 0; /* number of calls to 'command' */

void	get_cmd(t_line_char **cmd, char **env)
{
	int		i;
//	int		n;
	t_line_char	**tmp;
//	t_line_char	**args;

	(void)env;
	i = 0;
	while (cmd[i])
	{
		tmp = marked_split(cmd[i++], '|');
		if (tmp == NULL)
			return ;
		command(tmp, env);
		for (int j = 0 ; tmp[j] ; j++)
		{
			free(tmp[j]);
		}
//			n = 0;
//			command(args, env);
//			while (args[n])
//				free(args[n++]);
//			free(args);
		free(tmp);
	}
}

int main(int ac, char **av, char **env)
{
	char		*line;
	t_line_char	**cmd;

	(void)ac;
	(void)av;
	while (1)
	{
		printf("$> ");
		fflush(NULL);
		if (!get_next_line(0, &line))
			break ;
		cmd = parse(&line);
		get_cmd(cmd, env);
		for (int i = 0 ; cmd[i] ; i++)
		{
			free(cmd[i]);
			cmd[i] = NULL;
		}
		free(cmd);
/*		//cleanup(n);
		n = 0;
		free_strtab(cmd);
		free(line);*/
	}
	free(line);
	printf("exit\n");
	return (0);
}
