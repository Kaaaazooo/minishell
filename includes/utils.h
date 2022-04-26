/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:08:32 by sabrugie          #+#    #+#             */
/*   Updated: 2021/12/01 18:16:26 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>

char	*ft_itoa(char *dst, int n);
char	*ft_llutoa(char *dst, long long unsigned int n);
size_t	ft_strlen(char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strcpy(char *dst, const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	**free_strs(char **strs, int j);

char	*ft_strdup(const char *s);
char	*ft_strstr(const char *haystack, const char *needle);
int		len_array(char **array);
char	*ft_strchr(const char *s, int c);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_isdigit(int c);
char	*ft_strjoin_with_quote(char *s1, char *s2);
int		check_argv(char *str, int mode);
int		find_pwd(char **env);

#endif
