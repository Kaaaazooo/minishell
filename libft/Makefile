# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/10 19:12:22 by sabrugie          #+#    #+#              #
#    Updated: 2020/02/23 10:44:25 by sabrugie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc

HEADER = includes

OPTIONS = -I $(HEADER)
CFLAGS = -Wall -Werror -Wextra $(OPTIONS)

MEM_FUNC = $(addprefix mem_func/, ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_memset.c ft_memccpy.c ft_memchr.c ft_memcmp.c)
X_TO_Y_FUNC = $(addprefix x_to_y_func/, ft_atoi.c ft_tolower.c ft_toupper.c \
	ft_itoa.c ft_itoa_base.c)
IS_X_FUNC = $(addprefix is_x_func/, ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_isspace.c)
PUT_FUNC = $(addprefix put_func/, ft_putstr_fd.c ft_putendl_fd.c \
	ft_putchar_fd.c ft_putunbr_fd.c)
STR_FUNC = $(addprefix str_func/, ft_strchr.c ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_substr.c \
	ft_strdup.c ft_strjoin.c ft_strcpy.c ft_strcat.c ft_strtrim.c \
	ft_strmapi.c ft_strndup.c ft_split.c ft_strcmp.c)
ALLOC_FUNC = $(addprefix alloc_func/, ft_calloc.c)
LST_FUNC = $(addprefix lst_func/, ft_lstadd_front_bonus.c ft_lstdelone_bonus.c \
	ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c \
	ft_lstsize_bonus.c ft_lstadd_back_bonus.c ft_lstclear_bonus.c \
	ft_lstmap_bonus.c)

FT_PRINTF = $(addprefix ft_printf/, ft_printf.c conv_functions.c conv_functions2.c \
	parse.c length_modifiers.c double_functions.c double_functions2.c \
	double_functions3.c double_functions4.c num_functions.c ft_printf_utils.c \
	flags_functions.c)
GNL = $(addprefix gnl/, get_next_line.c get_next_line_utils.c)

SRCS = $(MEM_FUNC) $(X_TO_Y_FUNC) $(IS_X_FUNC) $(PUT_FUNC) $(STR_FUNC) \
	$(ALLOC_FUNC) $(LST_FUNC) $(GNL) $(FT_PRINTF)

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
bonus: $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS_BONUS)

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
