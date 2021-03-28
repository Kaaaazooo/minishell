/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:23:33 by sabrugie          #+#    #+#             */
/*   Updated: 2020/02/22 19:32:49 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_cpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	if (!d && !s)
		return (0);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

int		has_nl(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str++ == '\n')
			return (1);
	}
	return (0);
}

char	*ft_cut(char *s1)
{
	int		end;
	int		i;
	char	*res;

	i = 0;
	end = 0;
	if (s1 == 0)
		return (0);
	while (s1[end] && s1[end] != '\n')
		end++;
	if (!(res = malloc(sizeof(*res) * (end + 1))))
		return (0);
	while (i < end)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_join(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*str;

	if (!s1)
		return (ft_cut(s2));
	len1 = 0;
	len2 = 0;
	while (s1[len1])
		len1++;
	while (s2[len2] && s2[len2] != '\n')
		len2++;
	if (!(str = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (0);
	ft_cpy(str, s1, len1);
	ft_cpy(str + len1, s2, len2);
	str[len1 + len2] = 0;
	free(s1);
	return (str);
}

char	*to_next(int fd, char **remain, char *buf, int ret)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (i <= ret && buf[i] != '\n')
		i++;
	i++;
	if (ret == 0)
		ret = i;
	if (!(str = malloc(sizeof(char) * (ret - i + 1))))
		return (0);
	while (i + j < ret)
	{
		str[j] = buf[i + j];
		j++;
	}
	str[j] = 0;
	free(remain[fd]);
	return (str);
}
