#include "minishell.h"

t_line_char	*lc_allocenv(t_line_char **marked, char **env, int *i, int n)
{
	int		len;
	t_line_char	*new;
	char		*name;

	name = lcndup((*marked) + *i, n);
	if (name == NULL)
		return (NULL);
	*env = getenv(name);
	free(name);
	len = 0;
	while ((*marked)[len].c)
		++len;
	if (*env)
		new = calloc(sizeof(*new) , len + ft_strlen(*env) - n + 1);
	else
		new = calloc(sizeof(*new) , len - n + 1);
	return (new);
}

t_line_char	*expand_param(t_line_char **marked, int *i, int n)
{
	int		j;
	char		*env;
	t_line_char	*new;

	new = lc_allocenv(marked, &env, i, n);
	if (new == NULL)
		return (NULL);
	j = 0;
	--(*i);
	while (j < *i)
	{
		new[j] = (*marked)[j];
		++j;
	}
	while (env && *env)
	{
		new[*i].flag = M_ENV_VAR;
		new[(*i)++].c = *env++;
	}
	n += j + 1;
	j = *i;
	while ((*marked)[n].c)
		new[j++] = (*marked)[n++];
	free(*marked);
	return (new);
}

void	mark_env(t_line_char **marked)
{
	int	i;
	int	n;

	i = 0;
	while ((*marked)[i].c)
	{
		if ((*marked)[i].c == '$' && !((*marked)[i].flag & M_QUOTED) &&
				!((*marked)[i].flag & M_ESCAPED))
		{
			++i;
			n = 0;
			if (ft_isdigit((*marked)[i + n].c))
				++n;
			else
				while (ft_isalnum((*marked)[i + n].c) ||
						(*marked)[i + n].c == '_')
					++n;
			*marked = expand_param(marked, &i, n);
		}
		else
			++i;
	}
}

