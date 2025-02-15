#include "../libraries/minilibx-linux/mlx.h"
#include "../includes/so_long.h"
#include <stdlib.h>
#include <stdio.h>

#define WIDTH   800
#define HIGHT   600




int load_spirets(t_game *game)
{
    int (width), (height);

    width = 32;
    height = 32;

    game->player_sprite = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/player.xpm", &width, &height);
    game->wall_sprite = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/wall.xpm", &width, &height);
    game->collectible_sprite = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/collectible.xpm", &width, &height);
    game->exit_sprite = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/exit.xpm", &width, &height);
    game->floor_sprite = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/floor.xpm", &width, &height);
    if (!game->player_sprite || !game->collectible_sprite || !game->wall_sprite || !game->exit_sprite || !game->floor_sprite)
    {
        printf("Erorr : failed to load the sprites!\n");
        return (0);
    }
    return (1);
}

void render_map(t_game *game)
{
    // int (x), (y);
    // int (i), (j);
    
    // i = 0;
    // // while (i < game->dataMap->rows)
    // // {
    //     j = 0;
    // //     while (j < game->dataMap->cols)
    // //     {
    //         x = j * 32;
    //         y = i * 32;
            // if (game->dataMap->map[0][0] == WALL)
            //     mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->wall_sprite, x, y);
            // else if (game->dataMap->map[i][j] == EMPTY)
            //     mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->floor_sprite, x, y);
            // else if (game->dataMap->map[i][j] == COLLECTIBLE)
            //     mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->collectible_sprite, x, y);
            // else if (game->dataMap->map[i][j] == EXIT)
            //     mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->exit_sprite, x, y);
            // else if (game->dataMap->map[i][j] == PLAYER)
            //     mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->player_sprite, x, y);
    //         j++;
    //     }
    //     i++;
    // }
    printf("number %d\n", game->dataMap->map[0][0]);
}
int main() {
    t_game *gameData = malloc(sizeof(t_game));
    if (!read_map(gameData->dataMap))
        printf("map problem!\n");
    gameData->mlx_ptr = mlx_init();
    if (!gameData->mlx_ptr)
        return (1);

    gameData->win_ptr = mlx_new_window(gameData->mlx_ptr, WIDTH, HIGHT, "Game : mohamed");
    if (!gameData->win_ptr)
        return (free(gameData->mlx_ptr),1);
    if (!load_spirets(gameData))
        return (0);
    printf("number %d\n", gameData->dataMap->map[0][0]);
    // render_map(gameData);
    mlx_loop(gameData->mlx_ptr);
    // mlx_destroy_window(gameData->mlx_ptr,gameData->win_ptr);
    // mlx_destroy_display(gameData->mlx_ptr);
    // free(gameData->mlx_ptr);
    return 1;
}