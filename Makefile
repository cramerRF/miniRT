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
		./src/objs/properties.c \
		./src/objs/sphere.c \
		./src/objs/plane.c \
		./src/objs/triangle.c \
		./src/render/init.c \
		./src/render/add.c \
		./src/render/edit.c \
		./src/render/free.c \
		./src/render/menu.c \
		./src/render/update.c \
		./src/3dmath/utils1.c \


HEAD		= ./inc/miniRT.h \
		  ./inc/structs.h

LIB		= ./lib/libft/libft.a  -lm

LIB_MAC = -framework OpenGL -framework AppKit -L. -D RT_MACOS_COMPI ./lib/minilibx_macos/libmlx.a

LIB_LINUX	=  -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lz -D RT_LINUX_COMPI
#

OBJS_AUX	= $(SRC:.c=.o)
OBJS		= $(shell echo $(OBJS_AUX) | sed 's/\//_/g' | sed 's/\._/objs\//g')

GNL		=	./lib/gnl/get_next_line_bonus.c\
			./lib/gnl/get_next_line_utils_bonus.c

GNL_OBJS_AUX = ${GNL:.c=.o}
GNL_OBJS		= $(shell echo $(GNL_OBJS_AUX) | sed 's/\//_/g' | sed 's/\._/objs\//g')

CC		= cc

CFLAGS		= -Wall -Wextra -Werror -g3	 #-fsanitize=address

NAME		= miniRT

.c.o:
			${CC} ${CFLAGS} -c $< -o ./objs/$(shell echo $(patsubst %.c,%.o,$<) | sed 's/\//_/g')

${NAME}:	MAC

LINUX:		${OBJS_AUX} ${GNL_OBJS_AUX} ${HEAD}
			make bonus -C ./lib/libft
			make re -C ./lib/minilibx_linux
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${GNL_OBJS} ${LIB} ${LIB_LINUX}

MAC:		${OBJS_AUX} ${GNL_OBJS_AUX} ${HEAD}
			make bonus -C ./lib/libft
			make -C ./lib/minilibx_macos
			${CC} ${CFLAGS} -D RT_MACOS_COMPI -o ${NAME} ${OBJS} ${GNL_OBJS} ${LIB} ${LIB_MAC}

all:		${NAME}

clean:
			make clean -C ./lib/libft
			${RM} ${OBJS} ${GNL_OBJS}

fclean:		clean
			${RM} ${NAME}
			make fclean -C ./lib/libft
			make clean -C ./lib/minilibx_macos
			
re:			fclean all

.PHONY:	all clean fclean re
