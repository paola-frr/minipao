MANDATORY_SRCS = ./ft_isalpha.c\
				 ./ft_isdigit.c\
				 ./ft_isalnum.c\
				 ./ft_isascii.c\
				 ./ft_isprint.c\
				 ./ft_strlen.c\
				 ./ft_memset.c\
				 ./ft_bzero.c\
				 ./ft_memcpy.c\
				 ./ft_memmove.c\
				 ./ft_strlcpy.c\
				 ./ft_strlcat.c\
				 ./ft_toupper.c\
				 ./ft_tolower.c\
				 ./ft_strchr.c\
				 ./ft_strrchr.c\
				 ./ft_strncmp.c\
				 ./ft_memchr.c\
				 ./ft_memcmp.c\
				 ./ft_strnstr.c\
				 ./ft_freetab.c\
				 ./ft_realloc.c\
				 ./ft_atoi.c\
				 ./ft_calloc.c\
				 ./ft_strdup.c\
				 ./ft_substr.c\
				 ./ft_strjoin.c\
				 ./ft_putchar_fd.c\
				 ./ft_putstr_fd.c\
				 ./ft_putendl_fd.c\
				 ./ft_putnbr_fd.c\
				 ./ft_strmapi.c\
				 ./ft_strtrim.c\
				 ./ft_strcmp.c\
				 ./ft_itoa.c\
				 ./ft_printf.c\
				 ./ft_printf_utils.c\
				 ./ft_striteri.c\
				 ./ft_split.c \
				 ./supstrjoin.c \
				 ./get_next_line.c \
				 ./get_next_line_utils.c \
				 ./ft_isalpha_.c \
				 ./ft_isspace.c \
				 ./ft_split_isspace.c \
				 ./ft_strlen_tab.c

BONUS_SRCS = ./ft_lstnew.c\
			 ./ft_lstadd_front.c\
			 ./ft_lstsize.c\
			 ./ft_lstlast.c\
			 ./ft_lstadd_back.c\
			 ./ft_lstdelone.c\
			 ./ft_lstclear.c\
			 ./ft_lstiter.c\
			 ./ft_lstmap.c

MANDATORY_OBJS = ${MANDATORY_SRCS:.c=.o}

BONUS_OBJS = ${BONUS_SRCS:.c=.o}

NAME = libft.a 

CC = cc

CFLAGS = -Wall -Werror -Wextra

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:${MANDATORY_OBJS}
	ar rc ${NAME} ${MANDATORY_OBJS}
	ranlib ${NAME}

all:	${NAME}

bonus:	${BONUS_OBJS} ${NAME}
	ar rc ${NAME} ${MANDATORY_OBJS} ${BONUS_OBJS}
	ranlib ${NAME}

clean:
	rm -f ${MANDATORY_OBJS} ${BONUS_OBJS}

fclean: clean
		rm -f $(NAME)

re: fclean	all

.PHONY: all clean fclean re

