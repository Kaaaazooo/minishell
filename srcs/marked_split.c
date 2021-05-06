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

static t_line_char	**free_lctabs(t_line_char **strs, int j)
{
	while (j >= 0)
		free(strs[j--]);
	free(strs);
	return (NULL);
}

t_line_char	*lccpy(t_line_char *dst, t_line_char *src, int n)
{
	int	i;

	if (!dst || !src)
		return (NULL);
	i = 0;
	while (src[i].c && i < n)
	{
		dst[i] = src[i];
		++i;
	}
	return (dst);
}

t_line_char	**marked_split(t_line_char *s, char c)
{
	t_line_char	**res;
	size_t		i;
	size_t		j;

	if (!s)
		return (NULL);
	if (!(res = malloc(sizeof(*res) * (count(s, c) + 1))))
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
			if (!(res[j] = calloc(sizeof(**res), i + 1)))
				return (free_lctabs(res, (int)(j)));
			res[j] = lccpy(res[j], s, i);
			++j;
			s += i;
		}
	}
	res[j] = NULL;
	return (res);
}
