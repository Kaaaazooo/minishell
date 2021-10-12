NAME = minishell

HEADER = includes

OPTIONS = -I $(HEADER)
LDFLAGS = -L /Users/sabrugie/.brew/opt/readline -lreadline
LDFLAGS_LINUX = -lreadline
CFLAGS = -Wall -Werror -Wextra $(OPTIONS)

UTILS = $(addprefix utils/, ft_strlen.c ft_calloc.c ft_strcpy.c ft_strncmp.c ft_strndup.c)
PARSE = $(addprefix parse/, parse.c marked_split.c line_split.c split_word.c)
SIG_FUNC = $(addprefix sig_func/, sig_func.c)

SRCS = $(addprefix srcs/, $(UTILS) $(PARSE) $(SIG_FUNC) main.c)

CC = gcc

all: $(NAME)

OBJS = $(SRCS:.c=.o)

linux: $(OBJS)
	$(CC) $(CFLAGS) -o ./$(NAME) $(OBJS) $(LDFLAGS_LINUX)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o ./$(NAME) $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

relinux: fclean linux
