CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT = ./Libft/libft.a
SRCS = $(wildcard src/*.c) \
		# family.c \
		# main.c \
		# lidl_function.c \
		# not_so_lidl.c \
		# pipes.c \
		# basic.c \
		# path.c \
		# basic2.c \
		# debug_shit.c

INC = inc
NAME = minishell

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@make -C ./Libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) ${LIBFT} -o $(NAME) -lreadline

%.o : %.c
	${CC} -I${INC} -c -o $@ $<

clean:
	rm -rf $(OBJ)
	@make clean -C ./Libft

fclean: clean
	rm -rf $(NAME)
	@make fclean -C ./Libft

re: fclean all

# Mark these as not actual files
.PHONY: fclean clean all re
