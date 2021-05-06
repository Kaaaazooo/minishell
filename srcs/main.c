/* Compile with: g++ -Wall –Werror -o shell shell.c */

#include "minishell.h"

pid_t pid;

#define READ  0
#define WRITE 1

//int	free_strtab(char **tab)
//{
//	int	i;
//
//	i = 0;
//	while (tab[i])
//	{
//		free(tab[i]);
//		tab[i++] = NULL;
//	}
//	free(tab);
//	tab = NULL;
//	return (0);
//}
//
//void	getcmdpath(char **args, char **env)
//{
//	char	*tmp;
//	char	**paths;
//	char	**arg;
//	int	i;
//
//	tmp = getenv("PATH");
//	paths = line_split(tmp, ":", "\0");
//	arg = line_split(*args, " \t", "");
//	i = 0;
//	while (arg[i])
//	{
//		printf("arg[%d] = [%s]\n", i, arg[i]);
//		++i;
//	}
//	i = 0;
//	while (paths[i])
//	{
//		tmp = ft_strjoin(paths[i], "/");
//		free(paths[i]);
//		paths[i] = tmp;
//		tmp = ft_strjoin(paths[i], *arg);
//		if (execve(tmp, arg, env) != -1)
//		{
//			free(tmp);
//			free_strtab(arg);
//			break ;
//		}
//		free(tmp);
//		++i;
//	}
//	free_strtab(arg);
//	printf("\narg = %p\n\n", arg);
//}
//
//static int command(char **args, char **env)
//{
//	int i;
//	int j;
//	int pd[2];
//
//	i = 0;
//	printf("COMMAND FUNCTION :\n");
//	while (args[i])
//	{
//		printf("args[%d] = [%s]\n", i, args[i]);
//		++i;
//	}
//	if (!fork())
//	{
//		j = 0;
//		while (args[j])
//			++j;
//		for( i=0; i < j - 1; i++)
//		{
//			pipe(pd);
//			if (!fork()) {
//				dup2(pd[1], 1);
//				getcmdpath(&(args[i]), env);
//			}
//			wait(NULL);
//			printf("pd[0] = %d | pd [1] = %d\n", pd[0], pd[1]);
//			dup2(pd[0], 0);
//			close(pd[1]);
//		}
//		getcmdpath(&(args[i]), env);
//	}
//	else
//		wait(NULL);
//	return (0);
//}
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
//
//void	get_cmd(char **cmd, char **env)
//{
//	int	i;
//	int	j;
//	char	**args;
//
//	i = 0;
//	if (env == NULL)
//		command(cmd, env);
//	while (cmd[i])
//	{
//		j = 0;
//		args = line_split(cmd[i++], "|", "\n");
//		command(args, env);
//		while (args[j])
//		{
//			printf("args[%d] = [%s]\n", j, args[j]);
//			++j;
//		}
//		free(args);
//	}
//}
//
int main(int ac, char **av, char **env)
{
	char	*line;
	char	**cmd;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		printf("$> ");
		fflush(NULL);
		if (!get_next_line(0, &line))
			break ;
//		put_env(line);
		cmd = parse(&line);
		for (int i = 0 ; cmd[i] ; i++)
		{
			free(cmd[i]);
			cmd[i] = NULL;
		}
		free(cmd);
		continue ;
/*		cmd = line_split(line, ";", "\n");
		get_cmd(cmd, env);
		//cleanup(n);
		n = 0;
		free_strtab(cmd);
		free(line);*/
	}
	free(line);
	printf("exit\n");
	return (0);
}
