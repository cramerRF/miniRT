SRC		= ./src/main.c \
		./src/input_utils.c \
		./src/file_parser.c \
		./src/menu/menu.c \
		./src/menu/add.c \
		./src/menu/clean.c \
		./src/menu/delete.c \
		./src/menu/edit.c \
		./src/menu/error.c \
		./src/menu/exit.c \
		./src/menu/list.c \
		./src/camera/camera.c \
		./src/light/light.c \
		./src/light/ambient_light.c \
		./src/objs/plane.c \
		./src/objs/sphere.c \
		./src/objs/triangle.c

HEAD		= ./inc/miniRT.h \
		  ./inc/structs.h

LIB		= ./lib/libft/libft.a -lm

OBJS		= ${SRC:.c=.o}

GNL		=	./lib/gnl/get_next_line_bonus.c\
			./lib/gnl/get_next_line_utils_bonus.c

GNL_OBJS = ${GNL:.c=.o}

CC		= cc

CFLAGS		= -Wall -Wextra -Werror -g3

NAME		= miniRT

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${GNL_OBJS} ${HEAD}
			make bonus -C ./lib/libft
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${GNL_OBJS} ${LIB}

all:		${NAME}

clean:
			make clean -C ./lib/libft
			${RM} ${OBJS} ${GNL_OBJS}

fclean:		clean
			make fclean -C ./lib/libft
			${RM} ${NAME}

re:			fclean all

.PHONY:	all clean fclean re