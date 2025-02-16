#include "../libraries/minilibx-linux/mlx.h"
#include "../includes/so_long.h"
#include <stdlib.h>
#include <stdio.h>

#define WIDTH   575
#define HIGHT   255




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
    int (x), (y);
    int (i), (j);
    
    i = 0;
    while (i < game->dataMap->rows)
    {
        j = 0;
        while (j < game->dataMap->cols)
        {
            x = j * 64;
            y = i * 64;
            if (game->dataMap->map[i][j] == WALL)
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->wall_sprite, x, y);
            else if (game->dataMap->map[i][j] == EMPTY)
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->floor_sprite, x, y);
            else if (game->dataMap->map[i][j] == COLLECTIBLE)
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->collectible_sprite, x, y);
            else if (game->dataMap->map[i][j] == EXIT)
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->exit_sprite, x, y);
            else if (game->dataMap->map[i][j] == PLAYER)
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->player_sprite, x, y);
            j++;
        }
        i++;
    }
}

#include <stdlib.h>

void init_map_data(MapData *map_data)
{
    map_data->map = NULL;  // Later, you'll allocate and fill this
    map_data->rows = 0;
    map_data->cols = 0;
    map_data->player_count = 0;
    map_data->exit_count = 0;
    map_data->collectible_count = 0;
}

void init_game(t_game **game)
{
    (*game)->dataMap = (MapData *)malloc(sizeof(MapData));
    if (!(*game)->dataMap)
        return; // Handle allocation failure

    init_map_data((*game)->dataMap);

    (*game)->mlx_ptr = NULL;
    (*game)->win_ptr = NULL;
    (*game)->sprite_w_h = 32;  // Example sprite size
    (*game)->player_sprite = NULL;
    (*game)->wall_sprite = NULL;
    (*game)->collectible_sprite = NULL;
    (*game)->exit_sprite = NULL;
    (*game)->floor_sprite = NULL;
}

int main() {
    t_game *gameData;
    init_game(&gameData);
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
    render_map(gameData);
    mlx_loop(gameData->mlx_ptr);
    // mlx_destroy_window(gameData->mlx_ptr,gameData->win_ptr);
    // mlx_destroy_display(gameData->mlx_ptr);
    // free(gameData->mlx_ptr);
    return 1;
}