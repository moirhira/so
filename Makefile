NAME = so_long
NAME1 = so_long_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = 	src/main.c src/main_utils.c src/validate_map.c src/val_utils_1.c src/val_utils_2.c \
		libraries/get_next_line/get_next_line.c libraries/get_next_line/get_next_line_utils.c\

SRC_BONUS = src_bonus/main_bonus.c src_bonus/main_utils_bonus.c src_bonus/validate_map_bonus.c src_bonus/val_utils_1_bonus.c src_bonus/val_utils_2_bonus.c \
		libraries/get_next_line/get_next_line.c libraries/get_next_line/get_next_line_utils.c\
		
OBJ = ${SRC:.c=.o}
OBJ_BONUS = ${SRC_BONUS:.c=.o}
LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = libraries/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -L$(LIBFT_DIR) $(MLX_LIB) -L$(MLX_DIR) -I$(MLX_DIR) -lft -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

bonus: $(NAME1)

$(NAME1): $(OBJ_BONUS) $(LIBFT)
	$(CC) $(OBJ_BONUS) -L$(LIBFT_DIR) $(MLX_LIB) -L$(MLX_DIR) -I$(MLX_DIR) -lft -lXext -lX11 -lm -lz -o $(NAME1)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -O3 -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME) $(NAME1)

re: fclean all

.PHONY: all clean fclean re