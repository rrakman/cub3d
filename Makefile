NAME	:= CUB3D
CC := gcc
CFLAGS	:= -Wextra -Wall -Werror -g -fsanitize=address
LIBMLX	:= ../MLX42/build/libmlx42.a
LIBFLAGS := -framework Cocoa -framework OpenGL -framework IOKit
GLFWPATH := /Users/rrakman//MLX42/build/_deps/glfw-build/src/libglfw3.a
SRC = main.c
OBJ = ${SRC:%.c=%.o}

$(NAME): $(OBJ)
	$(CC) ${CFLAGS} ${LIBFLAGS} $(LIBMLX) ${GLFWPATH} $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re