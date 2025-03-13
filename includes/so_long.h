#ifndef SO_LONG_H
#define SO_LONG_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libraries/libft/libft.h"
#include "../libraries/get_next_line/get_next_line.h"
#include "../libraries/minilibx-linux/mlx.h"

#define WALL '1'
#define PLAYER 'P'
#define EXIT 'E'
#define COLLECTIBLE 'C'
#define EMPTY '0'

typedef struct s_data
{
   char **map;
   int rows;
   int cols;
   int player_count;
   int exit_count;
   int collectible_count;
   int player_x;
   int player_y;
}   MapData;

typedef struct s_game
{
    MapData *dataMap;
    int score;
    void *mlx_ptr;
    void *win_ptr;
    void *player_left;
    void *player_right;
    void *player_top;
    void *player_dowwn;
    void *player;
    void *wall_sprite;
    void *collectible_sprite;
    void *exit_sprite;
    void *floor_sprite;
} t_game;


// validate map
void fill_map_data(MapData **data);
int chek_walls(MapData **data, int first_col_ln);
int validate_map(MapData **data);
int ft_strlen(char *str);
void accessibility(MapData *data, int x, int y, int *colectibles_f, int *exit_f, int **visited);
int **allocate_visited_array(MapData *data);
int  check_accessibility(MapData *data);
int validate_file_extension(char *file);
int count_map_row(char *file);
char **allocate_and_read_map(int rows, char *file);
int read_map(MapData *new_map , char *file);

//main
int load_spirets(t_game *game);
void render_map(t_game *game);
void free_sprites(t_game *data);
int close_handler(t_game *data);

#endif