#include "../includes/so_long.h"

int load_spirets(t_game *game)
{
    int (width), (height);

    width = 64;
    height = 64;
    game->player_left = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/player_left.xpm", &width, &height);
    game->player_right = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/player_right.xpm", &width, &height);
    game->player_top = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/player_top.xpm", &width, &height);
    game->player_dowwn = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/player_down.xpm", &width, &height);
    game->player = game->player_right;
    game->wall_sprite = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/wall.xpm", &width, &height);
    game->collectible_sprite = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/collectible.xpm", &width, &height);
    game->exit_sprite = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/exit.xpm", &width, &height);
    game->floor_sprite = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/floor.xpm", &width, &height);
    if (!game->player_left || !game->player_right || !game->collectible_sprite || !game->wall_sprite || !game->exit_sprite || !game->floor_sprite || !game->player_dowwn || !game->player_top )
    {
        printf("Erorr : failed to load the sprites!\n");
        return (0);
    }
    return (1);
}

void render_map(t_game *game)
{
    int (x), (y), (i), (j);
    
    i = -1;
    while (++i < game->dataMap->rows)
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
            else if (game->dataMap->map[i][j] == EMPTY)
                mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->floor_sprite, x,y);
            j++;
        }
    }
}

void free_sprites(t_game *data)
{
     if (data->player_left)
        mlx_destroy_image(data->mlx_ptr, data->player_left);
    if (data->player_right)
        mlx_destroy_image(data->mlx_ptr, data->player_right);
    if (data->player_top)
        mlx_destroy_image(data->mlx_ptr, data->player_top);
    if (data->player_dowwn)
        mlx_destroy_image(data->mlx_ptr, data->player_dowwn);
    if (data->collectible_sprite)
        mlx_destroy_image(data->mlx_ptr, data->collectible_sprite);
    if (data->wall_sprite)
        mlx_destroy_image(data->mlx_ptr, data->wall_sprite);
    if (data->exit_sprite)
        mlx_destroy_image(data->mlx_ptr, data->exit_sprite);
    if (data->floor_sprite)
        mlx_destroy_image(data->mlx_ptr, data->floor_sprite);
}

int close_handler(t_game *data)
{
    int (i);
    free_sprites(data);
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
    exit(0);
}