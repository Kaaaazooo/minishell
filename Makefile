NAME = minishell

LIBFT_P = libft
HEADER = includes

OPTIONS = -I $(HEADER) -I $(LIBFT_P)/includes
CFLAGS = -Wall -Werror -Wextra $(OPTIONS)
LDFLAGS = -L $(LIBFT_P) -lft

BUILTINS = $(addprefix builtins/, echo.c ft_pwd.c ft_cd.c)

SRCS = $(addprefix srcs/, main.c line_split.c parse.c)

CC = gcc

all: $(NAME)

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	make -C $(LIBFT_P)
	$(CC) $(CFLAGS) -o ./$(NAME) $(OBJS) $(LDFLAGS)

clean:
	make -C $(LIBFT_P) clean
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(LIBFT_P)/libft.a
	rm -rf $(NAME)

re: fclean all
