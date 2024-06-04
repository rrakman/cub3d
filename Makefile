NAME	:= CUB3D
CC := gcc
CFLAGS	:= -Wextra -Wall -Werror #-g -fsanitize=address
LIBMLX	:= ../MLX42/build/libmlx42.a
LIBFLAGS := -framework Cocoa -framework OpenGL -framework IOKit
GLFWPATH := /Users/rrakman//MLX42/build/_deps/glfw-build/src/libglfw3.a
SRC = src/main.c src/player_moves.c src/player_moves_tools.c src/intersections.c src/raycasting.c src/math.c src/tools.c \
		parsing/check_n_w_e_s.c parsing/ft_split.c parsing/get_next_line_utils.c parsing/libft.c parsing/map_checks.c \
		parsing/file_to_data.c parsing/get_next_line.c parsing/init_data.c parsing/main_parsing.c parsing/norm.c \
		parsing/player_check.c parsing/tools.c

OBJ = ${SRC:%.c=%.o}

$(NAME): $(OBJ)
	@$(CC) ${CFLAGS} ${LIBFLAGS} $(LIBMLX) ${GLFWPATH} $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re