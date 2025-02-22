#ifndef SO_LONG_H
#define SO_LONG_H

#include "../libraries/get_next_line/get_next_line.h"

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
    int window_width;
    int window_height;
    int score;
    void *mlx_ptr;
    void *win_ptr;
    int sprite_w_h;
    void *player_sprite;
    void *wall_sprite;
    void *collectible_sprite;
    void *exit_sprite;
    void *floor_sprite;
} t_game;

int read_map(MapData *new_map );
#endif