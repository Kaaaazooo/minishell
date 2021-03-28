/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:41:35 by sabrugie          #+#    #+#             */
/*   Updated: 2021/03/08 12:43:51 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdint.h>
# include <wchar.h>

# ifndef BUF_SIZE
#  define BUF_SIZE	8
# endif

# define TRUE		1
# define FALSE		0

# define PREC		1
# define WIDTH		2
# define LEFT		4
# define ZERO		8
# define ALT_FORM	16
# define PLUS		32
# define SPACE		64
# define MINUS		128
# define L		256
# define LL		512
# define H		1024
# define HH		2048
# define NO_POINT	4096

# define W_SHIFT	32

typedef	long long unsigned int	t_llui;
typedef long long int			t_lli;

typedef struct	s_modifiers
{
	int			field_width;
	int			precision;
	int			count;
	short int	flags;
	char		buf[BUF_SIZE];
}				t_modif;

typedef union	u_double_to_int64
{
	double		d;
	int64_t		i;
}				t_dtoi64;

typedef struct	s_double_parts
{
	int32_t		sign;
	int64_t		exponent;
	int64_t		mantissa;
}				t_d_parts;

typedef struct	s_int64_parts
{
	uint32_t	high;
	uint32_t	low;
}				t_i64_parts;

int				ft_printf(const char *format, ...);

int				ft_skipatoi(char **str);
void			check_assign(t_modif *mod, char c);
int				get_len(char *str, t_modif *mod);
int				get_exp(char *nb, t_modif *mod, int len);
char			*ft_strrev(char *str);

short int		get_flags(char **s);
void			get_field(char **str, va_list ap, t_modif *mod);
void			get_precision(char **str, va_list ap, t_modif *mod);
void			get_length_modif(char **str, t_modif *mod);

int				c_conv(va_list ap, t_modif *mod);
int				percent_conv(t_modif *mod);
int				s_conv(va_list ap, t_modif *mod);
int				num_conv(va_list ap, int base, t_modif *mod);
int				u_num_conv(va_list ap, int base, t_modif *mod);
int				p_conv(va_list ap, int base, t_modif *mod);
int				n_conv(va_list ap, t_modif *mod);
int				f_conv(va_list ap, t_modif *mod);
int				e_conv(va_list ap, t_modif *mod);
int				g_conv(va_list ap, t_modif *mod);
int				new_g_conv(va_list ap, t_modif *mod, ...);

int				apply_field_width(t_modif *mod, int field_width);
int				apply_prec(t_modif *mod, int len);
int				apply_sign(int base, t_modif *mod);
int				apply_alt_form(int base, t_modif *mod);
int				pre_flags(int base, t_modif *mod);

t_lli			get_arg(va_list ap, t_modif *mod);
t_llui			u_get_arg(va_list ap, t_modif *mod);
t_lli			n_get_arg(t_modif *mod);
double			d_get_arg(va_list ap, t_modif *mod);

int				merge_num(char *nb, int len, t_modif *mod);
int				number_base(char *str, t_lli nb, int base);
int				u_number_base(char *str, t_llui nb, int base);
int				nb_len(int nb, int base);

int				ft_dtoa(char *str, double nb, t_modif *mod);
int				merge_double(char *nb, int len, t_modif *mod);
int				round_double(char *str, int precision, int len);
int				is_all_nine(char *str, int n);
int				move_dec_point(char *str, t_modif *mod, int len);
int				put_exp(int exp, char *nb, t_modif *mod);
void			change_mod(char *nb, int exp, t_modif *mod);
int				is_e_form(char *nb, int exp, int len, t_modif *mod);
uint64_t		mult_overflow(uint32_t mult, uint32_t *array, uint32_t n);
uint64_t		div_remainder(uint32_t divisor, uint32_t *array, uint32_t n);
int				set_dec_point(char *nb, t_modif *mod);

#endif
