SRC		= ./src/main.c \
		./src/input_utils.c \
		./src/gnl_utils.c \
		./src/file_parser.c \
		./src/menu/menu.c \
		./src/menu/add.c \
		./src/menu/delete.c \
		./src/menu/edit.c \
		./src/menu/error.c \
		./src/menu/exit.c \
		./src/menu/list.c \
		./src/menu/save.c \
		./src/menu/load.c \
		./src/menu/help.c \
		./src/camera/camera.c \
		./src/light/light.c \
		./src/light/ambient_light.c \
		./src/objs/plane.c \
		./src/objs/sphere.c \
		./src/objs/triangle.c

HEAD		= ./inc/miniRT.h \
		  ./inc/structs.h

LIB		= ./lib/libft/libft.a -lm

LIB_MAC = -lmlx -framework OpenGL -framework AppKit -L.

LIB_LINUX	= -L/usr/lib -LXext -LX11 -lz

OBJS		= ${SRC:.c=.o}

GNL		=	./lib/gnl/get_next_line_bonus.c\
			./lib/gnl/get_next_line_utils_bonus.c

GNL_OBJS = ${GNL:.c=.o}

CC		= cc

CFLAGS		= -Wall -Wextra -Werror

NAME		= miniRT

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	MAC

LINUX:		${OBJS} ${GNL_OBJS} ${HEAD}
			make bonus -C ./lib/libft
			make -C ./lib/minilibx_linux
			${CC} ${CFLAGS} -D RT_LINUX_COMPI -o ${NAME} ${OBJS} ${GNL_OBJS} ${LIB} ${LIB_LINUX}

MAC:		${OBJS} ${GNL_OBJS} ${HEAD}
			make bonus -C ./lib/libft
			make -C ./lib/minilibx_macos
			${CC} ${CFLAGS} -D RT_MACOS_COMPI -o ${NAME} ${OBJS} ${GNL_OBJS} ${LIB} ${LIB_MAC}

all:		${NAME}

clean:
			make clean -C ./lib/libft
			${RM} ${OBJS} ${GNL_OBJS}

fclean:		clean
			make fclean -C ./lib/libft
			make clean -C ./lib/minilibx_macos
			make clean -C ./lib/minilibx_linux
			${RM} ${NAME}

re:			fclean all

.PHONY:	all clean fclean re
