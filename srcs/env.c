/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:52:21 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/27 22:55:17 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_add(char *add)
{
	size_t	i;
	char	**new;

	i = 0;
	while (g_sh.env[i])
		++i;
	new = ft_calloc(i + 3, sizeof(char *));
	if (new == NULL)
	{
		free(new);
		return (NULL);
	}
	i = SIZE_MAX;
	while (g_sh.env[++i])
	{
		new[i] = ft_strndup(g_sh.env[i], ft_strlen(g_sh.env[i]));
		if (new[i] == NULL)
			return (free_strs(new, i));
	}
	new[i] = add;
	free_strs(g_sh.env, i);
	g_sh.env = new;
	return (g_sh.env);
}

int	ft_putenv(char *s)
{
	char	*new;
	size_t	n;
	size_t	i;

	new = ft_strndup(s, ft_strlen(s));
	if (new == NULL)
		return (-1);
	n = 0;
	while (s[n] && s[n] != '=')
		++n;
	if (s[n] == 0)
		return (-1);
	i = SIZE_MAX;
	while (g_sh.env[++i])
		if (!ft_strncmp(g_sh.env[i], s, n) && (s[n] == '=' || !s[n]))
			break ;
	if (g_sh.env[i])
	{
		free(g_sh.env[i]);
		g_sh.env[i] = new;
	}
	else
		if (env_add(new) == NULL)
			return (-1);
	return (0);
}

char	**alloc_env(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		++i;
	g_sh.env = ft_calloc(i + 2, sizeof(char *));
	if (g_sh.env == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7))
			g_sh.env[i] = ft_strdup(env[i]);
		else
			g_sh.env[i] = ft_strndup(env[i], 6);
		if (g_sh.env[i++] == NULL)
		{
			free_strs(g_sh.env, --i);
			return (NULL);
		}
	}
	return (g_sh.env);
}

/*
//int	declare_env(char *str)
//{
//	size_t	i;
//	size_t	len;
//
//	if (ft_getenv(str))
//		return (0);
//	i = SIZE_MAX;
//	len = ft_strlen(str);
//	while (g_sh.env[++i])
//		if (!ft_strncmp(g_sh.env[i], str, len + 1))
//			break ;
//	if (env_add(str) == NULL)
//		return (-1);
//	return (0);
//}
*/

char	*ft_getenv(char *name)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (g_sh.env[i])
	{
		if (!ft_strncmp(name, g_sh.env[i], len) && g_sh.env[i][len] == '=')
			break ;
		++i;
	}
	if (g_sh.env[i])
		return (&(g_sh.env[i][len + 1]));
	else
		return (NULL);
}
