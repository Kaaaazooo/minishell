NAME = minishell

HEADER = includes

OPTIONS = -I $(HEADER)
LDFLAGS = -L /Users/sabrugie/.brew/opt/readline -lreadline
CFLAGS = -Wall -Werror -Wextra $(OPTIONS)

UTILS = $(addprefix utils/, ft_strlen.c ft_calloc.c)
PARSE = $(addprefix parse/, parse.c marked_split.c line_split.c)
SIG_FUNC = $(addprefix sig_func/, sig_func.c)

SRCS = $(addprefix srcs/, $(UTILS) $(PARSE) $(SIG_FUNC) main.c)

CC = gcc

all: $(NAME)

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o ./$(NAME) $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
