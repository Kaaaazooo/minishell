NAME = minishell

HEADER = includes

OPTIONS = -I $(HEADER) -I /Users/$(USER)/.brew/opt/readline/include
LDFLAGS = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline
LDFLAGS_LINUX = -lreadline
CFLAGS = -Wall -Werror -Wextra $(OPTIONS)

UTILS = $(addprefix utils/, ft_strlen.c ft_calloc.c ft_strcpy.c ft_strlcpy.c \
		ft_strncmp.c ft_strcmp.c ft_strndup.c free_strs.c is_x.c ft_split.c \
		ft_memset.c ft_memcpy.c ft_strjoin.c ft_itoa.c ft_strdup.c len_array.c \
		ft_strchr.c ft_strncpy.c ft_isdigit.c ft_strjoin_with_quote.c \
		check_argv.c find_pwd.c ft_strstr.c)

BUILTINS = $(addprefix builtins/, cd.c echo.c export.c unset.c \
		pwd.c exit.c env.c sorted_env.c ft_error_builtins.c)

PARSE = $(addprefix parse/, parse.c quote_is_closed.c split_word.c expand.c \
		merge_env.c mark_redir.c m_strlen.c m_str_conversions.c)

SRCS = $(addprefix srcs/, $(UTILS) $(PARSE) $(BUILTINS) main.c shlvl.c \
	   pipeline.c cmd.c try_error.c redir.c heredoc_utils.c heredoc.c \
	   wait_process.c env.c pipe_and_dup.c)
TEST_SRCS = $(addprefix srcs/, $(UTILS) $(PARSE) test.c)

CC = gcc

all: $(NAME)

OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

test: $(TEST_OBJS)
	$(CC) $(CFLAGS) -o ./$(NAME) $(TEST_OBJS) $(LDFLAGS_LINUX)

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
