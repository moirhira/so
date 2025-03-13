NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = 	src/main.c src/main_utils.c src/validate_map.c src/val_utils_1.c src/val_utils_2.c \
		libraries/get_next_line/get_next_line.c \
		libraries/get_next_line/get_next_line_utils.c\
		
OBJ = ${SRC:.c=.o}
LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = libraries/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -L$(LIBFT_DIR) $(MLX_LIB) -L$(MLX_DIR) -I$(MLX_DIR) -lft -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -O3 -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re