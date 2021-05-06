#include "minishell.h"

static size_t	count(t_line_char *s, char c)
{
	size_t		count;

	count = 0;
	while (s->c)
	{
		while (s->c == c)
			s++;
		count++;
		while (s->c && (s->c != c || s->flag & M_QUOTED ||
					s->flag & M_D_QUOTED ||
					s->flag & M_ESCAPED))
			s++;
	}
	return (count);
}

static char	**free_strs(char **strs, int j)
{
	while (j >= 0)
		free(strs[j--]);
	free(strs);
	return (NULL);
}

static char	*lcndup(t_line_char *s, int n)
{
	char	*new;
	int	i;

	new = ft_calloc(n + 1, 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new[i] = s[i].c;
		++i;
	}
	return (new);
}

char	**line_split(t_line_char *s, char c)
{
	char		**res;
	size_t		i;
	size_t		j;

	if (!s)
		return (NULL);
	if (!(res = malloc(sizeof(char*) * (count(s, c) + 1))))
		return (NULL);
	j = 0;
	while (s->c)
	{
		while (s->c == c)
			s++;
		i = 0;
		if (s->c)
		{
			while (s[i].c && (s[i].c != c || s[i].flag & M_QUOTED ||
						s[i].flag & M_D_QUOTED ||
						s[i].flag & M_ESCAPED))
				i++;
			if (!(res[j++] = lcndup(s, i)))
				return (free_strs(res, (int)(j - 1)));
			s += i;
		}
	}
	res[j] = NULL;
	return (res);
}
