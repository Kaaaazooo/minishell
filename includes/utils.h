/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:08:32 by sabrugie          #+#    #+#             */
/*   Updated: 2021/10/06 18:19:02 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strcpy(char *dst, const char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
