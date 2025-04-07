NAME = so_long
NAME_1 = so_long_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = 	src/main.c src/main_utils.c src/main_utils_2.c src/validate_map.c src/val_utils_1.c src/val_utils_2.c \
		libraries/get_next_line/get_next_line.c libraries/get_next_line/get_next_line_utils.c\

SRC_BONUS = src_bonus/main_bonus.c src_bonus/main_utils_bonus.c src_bonus/main_utils_2_bonus.c\
		 src_bonus/validate_map_bonus.c src_bonus/val_utils_1_bonus.c src_bonus/val_utils_2_bonus.c \
		libraries/get_next_line/get_next_line.c libraries/get_next_line/get_next_line_utils.c\
		
OBJ = ${SRC:.c=.o}
OBJ_BONUS = ${SRC_BONUS:.c=.o}
LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = /usr/include/minilibx-linux
PRINTF_DIR = libraries/printf
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF_LIB) $(OBJ)
	$(CC) $(OBJ) -L$(LIBFT_DIR) -L$(PRINTF_DIR) -L$(MLX_DIR) -lmlx -lft -lftprintf -lXext -lX11  -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

bonus: $(NAME_1)

$(NAME_1): $(LIBFT) $(PRINTF_LIB) $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) -L$(LIBFT_DIR) -L$(PRINTF_DIR) -L$(MLX_DIR) -lmlx -lft -lftprintf -lXext -lX11  -o $(NAME_1)

$(PRINTF_LIB):
	make -C $(PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -O3 -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(PRINTF_DIR)
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(PRINTF_DIR)
	rm -f $(NAME) $(NAME_1)

re: fclean all

.PHONY: all clean fclean re
