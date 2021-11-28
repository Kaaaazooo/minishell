/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_with_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:47:26 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/25 22:47:27 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_put_quote(char *p, char *s2)
{
	char	*pp;

	pp = p;
	while (*p != '=')
		p++;
	*p++ = '=';
	*p++ = '"';
	while (*s2)
		*p++ = *s2++;
	*p++ = '"';
	*p = '\0';
	return (pp);
}

char	*ft_strjoin_with_quote(char *s1, char *s2)
{
	char	*p;
	char	*pp;

	if (!s1 || !s2)
		return (NULL);
	p = (char *)malloc(sizeof(char) * ((ft_strlen(s1)) + (ft_strlen(s2)) + 3));
	if (!p)
		return (NULL);
	pp = p;
	while (*s1)
		*p++ = *s1++;
	while (*s2)
	{
		if (*s2 == '=')
		{
			*p = *s2++;
			return (ft_put_quote(pp, s2));
		}
		else
			*p++ = *s2++;
	}
	*p = '\0';
	return (pp);
}
