#include "minishell.h"

char	*lcs_to_strs(t_line_char *marked)
{
	int	i;
	int	n;
	char	*str;

	i = 0;
	n = 0;
	while (marked[i].c)
	{
		if (marked[i].flag ^ M_QU_START && marked[i].flag ^ M_QU_END &&
				marked[i].flag ^ M_ESCAPE)
				++n;
		++i;
	}
	str = calloc(1, n + 1);
	if (str == NULL)
		return (str);
	i = 0;
	n = 0;
	while (marked[i].c)
	{
		if (marked[i].flag ^ M_QU_START && marked[i].flag ^ M_QU_END &&
				marked[i].flag ^ M_ESCAPE)
				str[n++] = marked[i].c;
		++i;
	}
	return (str);
}
