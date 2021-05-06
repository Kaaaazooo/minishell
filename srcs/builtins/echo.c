#include "minishell.h"

int	echo(char *str)
{
	char flags;

	flags = 0;
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		if (ft_isspace(*(str + 2)))
		{
			str += 3;
			flags = 1;
		}
		else if (*(str + 2) == 0)
		{
			str += 2;
			flags = 1;
		}
	}
	ft_printf("[%s]", str);
	if (!flags)
		write(1, "\n",1);
	return (0);
}
