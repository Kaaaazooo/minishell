#include "minishell.h"

char	*merge(char **s1, char **s2, int *i)
{
	char	*new;

	new = ft_strjoin(*s1, *s2);
	if (new == NULL)
		return (NULL);
	free(*s1);
	*s1 = new;
	bzero(*s2, 1024);
	*i = 0;
	return (*s1);
}

void	expand_param(char **new, char **str)
{
	char	*env;
	char	*varname;
	char	*tmp;
	int	i;

	++(*str);
	tmp = NULL;
	i = 0;
	if (ft_isdigit(**str))
		++i;
	else
		while ((*str)[i] && (ft_isalnum((*str)[i]) ||
					(*str)[i] == '_'))
			++i;
	varname = ft_strndup(*str, i);
	if (varname == NULL)
		return ;
	env = getenv(varname);
	free(varname);
	tmp = ft_strjoin(*new, env);
	free(*new);
	*new = tmp;
	*str += i;
}

void	put_env(char *str)
{
	int	i;
	char	*buf;
	char	*new;

	i = 0;
	buf = ft_calloc(1025, sizeof(char));
	if (buf == NULL)
		return ;
	new = NULL;
	while (*str)
	{
		if (i == 1024)
		{
			merge(&new, &buf, &i);
			if (new == NULL)
				return ;
		}
		if (*str == '\'')
		{
			++str;
			while (*str && *str != '\'')
				buf[i++] = *(str++);
			if (*str)
				++str;
		}
		else if (*str == '\"')
		{
			++str;
			while (*str && *str != '\"')
			{
				if (*str == '\\' && char_in_str(str[1], "\\\"$"))
				{
						buf[i++] = str[1];
						str += 2;
				}
				else if (*str == '$')
				{
					merge(&new, &buf, &i);
					if (new == NULL)
						return ;
					expand_param(&new, &str);
				}
				else
				{
					buf[i++] = *str;
					++str;
				}
			}
			if (*str)
				++str;
		}
		else if (*str == '$')
		{
			merge(&new, &buf, &i);
			if (new == NULL)
				return ;
			expand_param(&new, &str);
		}
		else if (*str == '\\')
		{
			buf[i++] = str[1];
			str += 2;
		}
		else
		{
			buf[i++] = *str;
			++str;
		}
	}
	merge(&new, &buf, &i);
	printf("new = [%s]\n", new);
	free(new);
	free(buf);
}
