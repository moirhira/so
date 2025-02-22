#include "../libraries/minilibx-linux/mlx.h"
#include "../includes/so_long.h"
#include <stdlib.h>
#include <stdio.h>

int load_spirets(t_game *game)
{
    int (width), (height);

    width = 64;
    height = 64;

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
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->floor_sprite, 0,0);
    i = 0;
    while (i < game->dataMap->rows)
    {
        j = 0;
        while (j <= game->dataMap->cols)
        {
            x = j * 64;
            y = i * 64;
            if (game->dataMap->map[i][j] == WALL)
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->wall_sprite, x, y);
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

int close_handler(t_game *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    exit(0);
}

void update_game_state(t_game *data, int new_x, int new_y)
{
    if (data->dataMap->map[new_x][new_y] == 'C')
    {
        data->score++;
        printf("score : %d\n",data->score);
    }
    else if (data->dataMap->map[new_x][new_y] == 'E')
    {
        if (data->dataMap->collectible_count == data->score)
        {
            printf("You win!\n");
            close_handler(data);
            return;
        }
        else
        {
            printf("You need to collect all collectibles before exiting!\n");
            return; 
        }
    }
    data->dataMap->map[data->dataMap->player_x][data->dataMap->player_y] = '0';
    data->dataMap->player_x = new_x;
    data->dataMap->player_y = new_y;
    data->dataMap->map[new_x][new_y] = 'P';
}
int key_handler(int keycode, t_game *data)
{
    static int movement = 0;
    int new_x = data->dataMap->player_x;
    int new_y = data->dataMap->player_y;

    printf("Key pressed: %d\n", keycode);
    if (keycode == 65307)
        close_handler(data);
    else if (keycode == 65361) // left
        new_y--;
    else if (keycode == 65363) // right
        new_y++;
    else if (keycode == 65362) // up
        new_x--;
    else if (keycode == 65364) // down
        new_x++;
    if (new_x >= 0 && new_x < data->dataMap->rows &&
        new_y >= 0 && new_y < data->dataMap->cols &&
        data->dataMap->map[new_x][new_y] != '1')
    {
        update_game_state(data, new_x, new_y);
        movement++;
         printf("Movements: %d\n", movement);
    }
    else
    {
        printf("Movement impossible!\n");
    }
    return (0);
}

int loop_hook(t_game *game)
{
    mlx_clear_window(game->mlx_ptr, game->win_ptr);
    render_map(game);
    return(1);
}

int main() {
    t_game *gameData = malloc(sizeof(t_game));
    gameData->dataMap = malloc(sizeof(MapData));
    if (!read_map(gameData->dataMap))
    {
        printf("map problem!\n");
        free(gameData);
    }
    else
    {
        gameData->window_height = 64 * gameData->dataMap->rows;
        gameData->window_width = 64 * gameData->dataMap->cols;
        gameData->mlx_ptr = mlx_init();
        if (!gameData->mlx_ptr)
            return (0);

        gameData->win_ptr = mlx_new_window(gameData->mlx_ptr, gameData->window_width, gameData->window_height, "Game : mohamed");
        if (!gameData->win_ptr)
            return (free(gameData->mlx_ptr),1);
        if (!load_spirets(gameData))
            return (0);
        mlx_hook(gameData->win_ptr, 2, 1L << 0, key_handler, gameData);
        mlx_hook(gameData->win_ptr, 17, 0, close_handler, gameData);
        mlx_loop_hook(gameData->mlx_ptr, loop_hook, gameData);
        mlx_loop(gameData->mlx_ptr);
        // free(gameData->mlx_ptr);
    }
    return 1;
}