#include "../libraries/minilibx-linux/mlx.h"
#include "../includes/so_long.h"
#include <stdlib.h>
#include <stdio.h>

int load_spirets(t_game *game)
{
    int (width), (height);

    width = 64;
    height = 64;

     game->collectible_sprite = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/star.xpm", &width, &height);
    game->player_left = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/player_left.xpm", &width, &height);
    game->player_right = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/player_right.xpm", &width, &height);
    game->player = game->player_right;
    game->wall_sprite = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/wall.xpm", &width, &height);
    // game->collectible_sprite = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/collectible.xpm", &width, &height);
    game->exit_sprite = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/exit.xpm", &width, &height);
    game->floor_sprite = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/floor.xpm", &width, &height);
    if (!game->player_left || !game->player_right || !game->collectible_sprite || !game->wall_sprite || !game->exit_sprite || !game->floor_sprite)
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
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->player, x, y);
            j++;
        }
        i++;
    }
}

int close_handler(t_game *data)
{
    if (data->player_left)
        mlx_destroy_image(data->mlx_ptr, data->player_left);
    if (data->player_right)
        mlx_destroy_image(data->mlx_ptr, data->player_right);
    if (data->collectible_sprite)
        mlx_destroy_image(data->mlx_ptr, data->collectible_sprite);
    if (data->wall_sprite)
        mlx_destroy_image(data->mlx_ptr, data->wall_sprite);
    if (data->exit_sprite)
        mlx_destroy_image(data->mlx_ptr, data->exit_sprite);
    if (data->floor_sprite)
        mlx_destroy_image(data->mlx_ptr, data->floor_sprite);
    int i;
    if (data->dataMap)
    {
        i = 0;

        while (i < data->dataMap->rows)
        {
            free(data->dataMap->map[i]);
            i++;
        }
        free(data->dataMap->map);
    }
    if (data->win_ptr)
         mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    if (data->mlx_ptr)
        mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
    free(data->dataMap);
    free(data);

    // Exit the program
    exit(0);
}

void update_game_state(t_game *data, int new_x, int new_y, int direction)
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
    if (direction == 65361) // left
        data->player = data->player_left;
    else if (direction == 65363) // right
        data->player = data->player_right;
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

    // printf("Key pressed: %d\n", keycode);
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
        update_game_state(data, new_x, new_y,keycode);
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


int main(int ac, char **av)
{
    if (ac != 2)
    {
        printf("Usage: %s <filename>\n", av[0]);
        return 1;
    }

    t_game *gameData = malloc(sizeof(t_game));
    if (!gameData)
        return (0);
    gameData->dataMap = malloc(sizeof(MapData));
    if(!gameData->dataMap)
    {
        free(gameData);
        return (0);
    }
    
    if (!read_map(gameData->dataMap, av[1]))
    {
        printf("map problem!\n");
        free(gameData->dataMap);
        free(gameData);
        return (0);
    }
    else
    {
        void *mlx = mlx_init();
        if (!mlx)
            return (0);
        gameData->mlx_ptr = mlx;
        gameData->win_ptr = mlx_new_window(gameData->mlx_ptr, 64 * gameData->dataMap->cols, 64 * gameData->dataMap->rows, "Game : mohamed");
        if (!gameData->win_ptr)
            return (free(gameData->mlx_ptr),1);
        if (!load_spirets(gameData))
            close_handler(gameData);
        gameData->score = 0;
        mlx_hook(gameData->win_ptr, 2, 1L << 0, key_handler, gameData);
        mlx_hook(gameData->win_ptr, 17, 0, close_handler, gameData);
        mlx_loop_hook(gameData->mlx_ptr, loop_hook, gameData);
        mlx_loop(gameData->mlx_ptr);
        close_handler(gameData);
    }
    return 1;
}