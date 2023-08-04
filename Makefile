SRC		= ./src/main.c \

HEAD		= ./inc/miniRT.h \
		  ./inc/structs.h

LIB		= 

OBJS		= ${SRC:.c=.o}

GNL		=	./lib/gnl/get_next_line_bonus.c\
			./lib/gnl/get_next_line_utils_bonus.c

GNL_OBJS = ${GNL:.c=.o}

CC		= cc

CFLAGS		= -Wall -Wextra -Werror

NAME		= miniRT

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${GNL_OBJS} ${HEAD}
			make -C bonus ./lib/libft
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${GNL_OBJS} ${LIB}

all:		${NAME}

clean:
			make -C clean ./lib/libft
			${RM} ${OBJS} ${GNL_OBJS}

fclean:		clean
			make -C fclean ./lib/libft
			${RM} ${NAME}

re:			fclean all

.PHONY:	all clean fclean re