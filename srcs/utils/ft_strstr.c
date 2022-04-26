/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moakouda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:33:18 by moakouda          #+#    #+#             */
/*   Updated: 2021/11/29 16:33:31 by moakouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*ph;
	char	*pn;
	char	*p;

	ph = (char *)haystack;
	p = (char *)haystack;
	if (*needle == 0)
		return (p);
	while (*p)
	{
		ph = p;
		pn = (char *)needle;
		while (*ph == *pn)
		{
			pn++;
			ph++;
			if (*pn == '\0')
				return (p);
		}
		p++;
	}
	return (NULL);
}
