/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:59:15 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/12 19:04:39 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand(char **str, size_t j)
{
	size_t	i;
	char	tmp;
	char	*env;
	char	*new;

	i = 0;
	if (ft_isalpha((*str)[j + i]) || (*str)[j + i] == '_')
		while ((*str)[j + ++i])
			if (!ft_isalnum((*str)[j + i]) && (*str)[j + i] != '_')
				break ;
	tmp = (*str)[j + i];
	(*str)[j + i] = 0;
	env = getenv((*str) + j);
	(*str)[j + i] = tmp;
	new = ft_calloc(ft_strlen(*str) + ft_strlen(env) - (i + 1), sizeof(char));
	if (new == NULL)
		return (-1);
	strncpy(new, *str, j - 1);
	strcpy(new + ft_strlen(new), env);
	strcpy(new + ft_strlen(new), (*str) + j + i);
	free(*str);
	*str = new;
	return (0);
}
//	printf("new = [%s]\n", new);
//	printf("strlen(str) = %zu\n", ft_strlen(*str));
//	printf("i = %zu\n", i);
//	printf("var : [%s] = [%s]\n", (*str) + j, env);
//	printf("len var = %zu\n", ft_strlen(env));
//	printf("len new = %lu\n", ft_strlen(*str) + ft_strlen(env) - (i + 1));
//	printf("str = [%s] | j = %zu\n", *str, j);

int	expansions(t_token **token)
{
	size_t	i;
	size_t	j;
	char	*end_quote;

	i = 0;
	end_quote = NULL;
	while ((*token)[i].str)
	{
		j = 0;
		while ((*token)[i].str[j])
		{
			if (&((*token)[i].str[j]) > quoted(&((*token)[i].str[j]),
						&end_quote) || *end_quote == '"')
			{
				if ((*token)[i].str[j++] == '$')
					if ((*token)[i].str[j] && expand(&((*token)[i].str), j))
						return (-1);
			}
			else
				++j;
		}
		++i;
	}
	return (0);
}

t_token	*parse(char *buf)
{
	char	**word;
	t_token	*token;
	size_t	i;

	word = ft_calloc(count_words(buf) + 1, sizeof(char *));
	token = ft_calloc(count_words(buf) + 1, sizeof(t_token));
	if (token == NULL || word == NULL)
		return (NULL);
	split_word(&word, buf);
	i = 0;
	printf("nb of words = %d\n", count_words(buf));
	while (word[i])
	{
		token[i].str = word[i];
		if (is_metachar(word[i]) && is_metachar(word[i]) != BLANK)
			token[i].flag = 1;
		++i;
	}
	if (expansions(&token))
		return ((t_token *)free_strs(word, count_words(buf)));
	for (size_t i = 0; token[i].str; i++)
		printf("token[%zu] = [%s] (%d)\n", i, token[i].str, token[i].flag);
	return (NULL);
}
