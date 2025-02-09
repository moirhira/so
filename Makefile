NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra 
SRC = src/main.c src/validate_map.c libraries/get_next_line/get_next_line.c \
		libraries/get_next_line/get_next_line_utils.c
OBJ = ${SRC:.c=.o}
MLX_DIR = libraries/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LIB) -L$(MLX_DIR) -I$(MLX_DIR) -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -O3 -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re