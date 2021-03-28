/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 10:19:40 by sabrugie          #+#    #+#             */
/*   Updated: 2019/10/16 16:08:39 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (*needle == 0 || needle == 0)
		return ((char*)haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		while (needle[j] == haystack[i + j] && i + j < len)
		{
			j++;
			if (needle[j] == 0)
				return ((char*)&haystack[i]);
		}
		i++;
	}
	return (0);
}
