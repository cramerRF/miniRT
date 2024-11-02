SRCS_PATH = src/
INCS_PATH = inc/
BIN_PATH = bin/

SRCS		= main.c \
		input_utils.c \
		gnl_utils.c \
		file_parser.c \
		menu/menu.c \
		menu/add.c \
		menu/delete.c \
		menu/edit.c \
		menu/error.c \
		menu/exit.c \
		menu/list.c \
		menu/save.c \
		menu/load.c \
		menu/help.c \
		camera/camera.c \
		light/light.c \
		light/ambient_light.c \
		objs/properties.c \
		objs/sphere.c \
		objs/plane.c \
		objs/triangle.c \
		render/init.c \
		render/add.c \
		render/edit.c \
		render/free.c \
		render/menu.c \
		render/update.c \
		render/objs/plane.c \
		render/objs/sphere.c \
		render/objs/triangle.c \
		3dmath/utils1.c \
		gnl/get_next_line_bonus.c \
		gnl/get_next_line_utils_bonus.c \

HEAD		= inc/miniRT.h \
		  inc/structs.h

LIB		= lib/libft/libft.a  -lm

LIB_MAC = -framework OpenGL -framework AppKit -L. -D RT_MACOS_COMPI lib/minilibx_macos/libmlx.a

LIB_LINUX	= -std=gnu99 -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lz -D RT_LINUX_COMPI

OBJS 		= $(SRCS:%.c=bin/%.o)

CC		= cc

CFLAGS		= -Wall -Wextra -Werror -g3	#-fsanitize=address 

RM 				= rm -rf

NAME		= miniRT

all:		${NAME}

$(BIN_PATH)%.o: $(SRCS_PATH)%.c
			mkdir -p $(dir $@)
			$(CC) $(CFLAGS) -c $< -o $@

${NAME}:	LINUX

# LINUX:
LINUX:		${OBJS} ${GNL_OBJS} ${HEAD}
			echo OBJS ${OBJS}
			echo OBJS ${GNL_OBJS}
			make bonus -C ./lib/libft
			make -C ./lib/minilibx_linux
			${CC} ${CFLAGS} -D RT_LINUX_COMPI -o ${NAME} ${OBJS} ${GNL_OBJS} ${LIB} ${LIB_LINUX}

MAC:		${OBJS} ${GNL_OBJS} ${HEAD}
			make bonus -C ./lib/libft
			make -C ./lib/minilibx_macos
			${CC} ${CFLAGS} -D RT_MACOS_COMPI -o ${NAME} ${OBJS} ${GNL_OBJS} ${LIB} ${LIB_MAC}


clean:
			make clean -C ./lib/libft
			${RM} ${OBJS} ${GNL_OBJS}
			${RM} ${BIN_PATH}

fclean:		clean
			${RM} ${NAME}
			make fclean -C ./lib/libft
			make clean -C ./lib/minilibx_macos
			
re:			fclean all

run:  all
	./${NAME} ./rtFiles/sphere.rt

.PHONY:	all clean fclean re
