#include "minishell.h"

void	mark_quoted(t_line_char **marked, char *line, int i, uint8_t flag)
{
	(*marked)[i].c = *(line)++;
	if (!((*marked)[i].flag & M_QUOTED) &&
			!((*marked)[i].flag & M_D_QUOTED) &&
			!((*marked)[i].flag & M_ESCAPED))
		(*marked)[i++].flag |= M_QU_START;
	while (*line && ((flag & M_D_QUOTED && *line != '\"') || 
				(flag & M_QUOTED && *line != '\'') ||
				(*marked)[i].flag & M_ESCAPED))
	{
		(*marked)[i].c = *(line++);
		if (!((*marked)[i].flag & M_QUOTED) &&
				!((*marked)[i].flag & M_D_QUOTED))
			(*marked)[i++].flag |= flag;
	}
	(*marked)[i].c = *(line)++;
	if (!((*marked)[i].flag & M_QUOTED) &&
			!((*marked)[i].flag & M_D_QUOTED) &&
			!((*marked)[i].flag & M_ESCAPED))
		(*marked)[i++].flag |= M_QU_END;
}

void	mark_escape(t_line_char **marked, char *line, int i)
{
	if (!((*marked)[i].flag & M_QUOTED) && !((*marked)[i].flag & M_ESCAPED))
	{
		if (!((*marked)[i].flag & M_D_QUOTED) || line[1] == '$' ||
				line[1] == '\"' || line[1] == '\\')
		{
			(*marked)[i].flag |= M_ESCAPE;
			(*marked)[i++].c = *line++;
			(*marked)[i].flag |= M_ESCAPED;
			(*marked)[i++].c = *line++;
		}
	}
}

t_line_char	*expand_param(t_line_char **marked, char *line, int *i, int n)
{
	t_line_char	*new;
	char		*env;
	char		c;
	int		len;

	c = line[n];
	line[n] = 0;
	env = getenv(line);
	line[n] = c;
	//line[n] = (*marked)[i + n].c;
	len = 0;
	while ((*marked)[len].c)
		++len;
	if (env)
		new = calloc(sizeof(*new) , len + ft_strlen(env) - n + 1);
	else
		new = calloc(sizeof(*new) , len - n + 1);
	if (new == NULL)
		return (NULL);
	len = 0;
	while (len < *i)
	{
		new[len] = (*marked)[len];
		++len;
	}
	while (env && *env)
	{
		new[*i].flag = M_ENV_VAR;
		new[(*i)++].c = *env++;
	}
	n += len + 1;
	while ((*marked)[n].c)
		new[i++] = (*marked)[n++];
	for (int x = 0 ; new[x].c ; x++)
		printf("new[%d] = %c | %d\n", x, new[x].c, new[x].flag);
	free(*marked);
	return (new);
}

void	mark_env(t_line_char **marked, char *line, int i)
{
	int	n;

	while ((*marked)[i].c)
	{
		if ((*marked)[i].c == '$' && !((*marked)[i].flag & M_QUOTED) &&
				!((*marked)[i].flag & M_ESCAPED))
		{
			n = 0;
			printf("pre av : line [%s]\n", line);
			++line;
			printf("av : line [%s] | i = %d\n", line, i);
			if (ft_isdigit(*line))
				++n;
			else
				while (ft_isalnum(line[n]) || line[n] == '_')
					++n;
			*marked = expand_param(marked, line, &i, n);
			line += n;
			printf("ap : line [%s] | i = %d\n", line, i);
//			i += n;
		}
		else
		{
			++i;
			++line;
		}
	}
}

t_line_char	*mark_line(char *line)
{
	t_line_char	*marked;
	int		i;

	marked = ft_calloc(strlen(line) + 1, sizeof(t_line_char));
	if (marked == NULL)
		return (NULL);
	i = 0;
	while (*line)
	{
		if (!(marked[i].flag & M_QU_END) && !(marked[i].flag & M_ESCAPED))
		{
			if (*line == '\'')
				mark_quoted(&marked, line, i, M_QUOTED);
			else if (*line == '\"')
				mark_quoted(&marked, line, i, M_D_QUOTED);
		}
		if (*line == '\\')
			mark_escape(&marked, line, i);
		marked[i++].c = *line++;
	}
	mark_env(&marked, line - i, 0);
	return (marked);
}

char	**parse(char **line)
{
	t_line_char	*marked;
	char		**cmd;

	cmd = NULL;
	marked = mark_line(*line);
	if (marked == NULL)
		return (NULL);
	free(*line);
	cmd = line_split(marked, ';');
	for (int i = 0 ; cmd[i] ; i++)
		printf("cmd[%d] = [%s]\n", i, cmd[i]);
	*line = NULL;
	free(marked);
	return (cmd);
}
