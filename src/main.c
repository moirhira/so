#include "../libraries/minilibx-linux/mlx.h"
#include "../includes/so_long.h"
#include <stdlib.h>
#include <stdio.h>

#define WIDTH   800
#define HIGHT   600

typedef struct s_game
{
    void *mlx_ptr;
    void *win_ptr;
    int sprite_w_h;
    void *player_sprt;
} t_game;

int main() {
    if (!read_map())
        printf("map problem!\n");
    t_game *gameData = malloc(sizeof(t_game));
    gameData->mlx_ptr = mlx_init();
    if (!gameData->mlx_ptr)
        return (1);

    gameData->win_ptr = mlx_new_window(gameData->mlx_ptr, WIDTH, HIGHT, "Game : mohamed");
    if (!gameData->win_ptr)
        return (free(gameData->mlx_ptr),1);
    gameData->sprite_w_h = 32;
    gameData->player_sprt = mlx_xpm_file_to_image(gameData->mlx_ptr, "textures/player.xpm",&gameData->sprite_w_h,&gameData->sprite_w_h);
    if (!gameData->player_sprt)
    {
        printf("eroo loading player!\n");
        exit (1);
    }
    mlx_put_image_to_window(gameData->mlx_ptr, gameData->win_ptr, gameData->player_sprt,100 * gameData->sprite_w_h, 100 * gameData->sprite_w_h);
    mlx_loop(gameData->mlx_ptr);
    mlx_destroy_window(gameData->mlx_ptr,gameData->win_ptr);
    mlx_destroy_display(gameData->mlx_ptr);
    free(gameData->mlx_ptr);
    return 0;
}