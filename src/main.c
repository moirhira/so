
#include "../includes/so_long.h"





void update_game_state(t_game *data, int new_x, int new_y, int direction)
{
    if (data->dataMap->map[new_x][new_y] == 'C')
        printf("score : %d\n",++data->score);
    else if (data->dataMap->map[new_x][new_y] == 'E')
    {
        if (data->dataMap->collectible_count == data->score)
            return(void)(printf("You win!\n"),close_handler(data));
        return (void)(printf("You need to collect all collectibles before exiting!\n"));
    }
    if (direction == 65361)
        data->player = data->player_left;
    else if (direction == 65363)
        data->player = data->player_right;
    else if (direction == 65362)
        data->player = data->player_top;
    else if (direction == 65364)
        data->player = data->player_dowwn;
    data->dataMap->map[data->dataMap->player_x][data->dataMap->player_y] = '0';
    data->dataMap->player_x = new_x;
    data->dataMap->player_y = new_y;
    data->dataMap->map[new_x][new_y] = 'P';
}

int key_handler(int keycode, t_game *data)
{
    static int movement = 0;
    int (new_x),(new_y) ;
    new_x = data->dataMap->player_x;
    new_y = data->dataMap->player_y;
    if (keycode == 65307)
        close_handler(data);
    else if (keycode == 65361)
        new_y--;
    else if (keycode == 65363)
        new_y++;
    else if (keycode == 65362)
        new_x--;
    else if (keycode == 65364)
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
        printf("Movement impossible!\n");
    return (1);
}

int loop_hook(t_game *game)
{
    render_map(game);
    return(1);
}


int init_main(t_game **gameData, char *map)
{
    *gameData = malloc(sizeof(t_game));
    if (!*gameData)
        return (0);
    (*gameData)->dataMap = malloc(sizeof(MapData));
    if(!(*gameData)->dataMap)
    {
        free(*gameData);
        return (0);
    }
    if (!read_map((*gameData)->dataMap, map))
    {
        printf("map problem!\n");
        free((*gameData)->dataMap);
        free(*gameData);
        return (0);
    }
    return (1);
}

int main(int ac, char **av)
{
    t_game *gameData;

    if (ac != 2)
    {
        printf("%s\n","Usage: %s <filename>\n");
        return (0);
    }
    if (!init_main(&gameData, av[1]))
        return (0);
    gameData->mlx_ptr = mlx_init();
    if (!gameData->mlx_ptr)
        return (0);
    gameData->win_ptr = mlx_new_window(gameData->mlx_ptr, 64 * gameData->dataMap->cols, 64 * gameData->dataMap->rows, "Game : race");
    if (!gameData->win_ptr)
        return (free(gameData->mlx_ptr),1);
    if (!load_spirets(gameData))
        close_handler(gameData);
    mlx_hook(gameData->win_ptr, 2, 1L << 0, key_handler, gameData);
    mlx_hook(gameData->win_ptr, 17, 0, close_handler, gameData);
    mlx_loop_hook(gameData->mlx_ptr, loop_hook, gameData);
    mlx_loop(gameData->mlx_ptr);
    close_handler(gameData);
    return (1);
}
