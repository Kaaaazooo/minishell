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
	return (marked);
}

t_line_char	**parse(char **line)
{
	t_line_char	*marked;
	t_line_char	**cmd;

	cmd = NULL;
	marked = mark_line(*line);
	if (marked == NULL)
		return (NULL);
	free(*line);
	*line = NULL;
	cmd = marked_split(marked, ';');
	free(marked);
	return (cmd);
}
