NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iinc

SRC = src/

INC = inc/

FCTS =  $(SRC)fcts/ft_atoi.c $(SRC)fcts/ft_bzero.c $(SRC)fcts/ft_calloc.c $(SRC)fcts/ft_isalnum.c $(SRC)fcts/ft_isalpha.c $(SRC)fcts/ft_isascii.c \
		$(SRC)fcts/ft_isdigit.c $(SRC)fcts/ft_isprint.c $(SRC)fcts/ft_itoa.c $(SRC)fcts/ft_memchr.c $(SRC)fcts/ft_memcmp.c $(SRC)fcts/ft_memcpy.c \
		$(SRC)fcts/ft_memmove.c $(SRC)fcts/ft_memset.c $(SRC)fcts/ft_putchar_fd.c $(SRC)fcts/ft_putendl_fd.c $(SRC)fcts/ft_putnbr_fd.c \
		$(SRC)fcts/ft_putstr_fd.c $(SRC)fcts/ft_split.c $(SRC)fcts/ft_strchr.c $(SRC)fcts/ft_strdup.c $(SRC)fcts/ft_striteri.c $(SRC)fcts/ft_strjoin.c \
		$(SRC)fcts/ft_strlcat.c $(SRC)fcts/ft_strlcpy.c $(SRC)fcts/ft_strlen.c $(SRC)fcts/ft_strmapi.c $(SRC)fcts/ft_strncmp.c $(SRC)fcts/ft_strcmp.c $(SRC)fcts/ft_strnstr.c \
		$(SRC)fcts/ft_strrchr.c $(SRC)fcts/ft_strtrim.c $(SRC)fcts/ft_substr.c $(SRC)fcts/ft_tolower.c $(SRC)fcts/ft_toupper.c

FT_PRINTF = $(SRC)printf/ft_printf.c $(SRC)printf/all_ft_1.c $(SRC)printf/all_ft_2.c

GET_NEXT_LINE = $(SRC)get_next_line/get_next_line.c $(SRC)get_next_line/get_next_line_utils.c \
				$(SRC)get_next_line/get_next_line_bonus.c $(SRC)get_next_line/get_next_line_bonus.c

OBJS = $(SRCS:.c=.o)

SRCS = $(FCTS) $(FT_PRINTF) $(GET_NEXT_LINE)

ARRC = ar rc

RANLIB = ranlib

RM = rm -f

.c.o : $(SRCS)
	${CC} ${CFLAGS} -c -o $@ $^

$(NAME) : $(OBJS)
	$(ARRC) $(NAME) $(OBJS)
	$(RANLIB) $(NAME)

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all


.PHONY : all clean fclean re
