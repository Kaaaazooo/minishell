/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:46:48 by sabrugie          #+#    #+#             */
/*   Updated: 2021/11/25 22:46:51 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup(const char *s)
{
	char	*ps;

	ps = (char *)malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (!ps)
		return (NULL);
	ft_strcpy(ps, s);
	return (ps);
}
