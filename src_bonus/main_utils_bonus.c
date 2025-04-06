/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:47:55 by moirhira          #+#    #+#             */
/*   Updated: 2025/03/14 20:22:25 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

int	load_spirets_helper(t_game *game)
{
	if (!game->player_left || !game->player_right || !game->collectible_sprite
		|| !game->wall_sprite || !game->exit_sprite || !game->floor_sprite
		|| !game->player_dowwn || !game->player_top || !game->enemy)
		return (printf("Err: failed load sprites!\n"), 0);
	return (1);
}

int	load_spirets(t_game *game)
{
	int (w), (h);
	1 && (w = 64, h = 64);
	game->player_left = mlx_xpm_file_to_image(game->mlx_ptr,
			"spiretes/player_left.xpm", &w, &h);
	game->player_right = mlx_xpm_file_to_image(game->mlx_ptr,
			"spiretes/player_right.xpm", &w, &h);
	game->player_top = mlx_xpm_file_to_image(game->mlx_ptr,
			"spiretes/player_top.xpm", &w, &h);
	game->player_dowwn = mlx_xpm_file_to_image(game->mlx_ptr,
			"spiretes/player_down.xpm", &w, &h);
	game->player = game->player_right;
	game->wall_sprite = mlx_xpm_file_to_image(game->mlx_ptr,
			"spiretes/wall.xpm", &w, &h);
	game->collectible_sprite = mlx_xpm_file_to_image(game->mlx_ptr,
			"spiretes/collectible.xpm", &w, &h);
	game->exit_sprite = mlx_xpm_file_to_image(game->mlx_ptr,
			"spiretes/exit.xpm", &w, &h);
	game->floor_sprite = mlx_xpm_file_to_image(game->mlx_ptr,
			"spiretes/floor.xpm", &w, &h);
	game->enemy = mlx_xpm_file_to_image(game->mlx_ptr, "spiretes/enemy.xpm", &w,
			&h);
	if (!load_spirets_helper(game))
		return (0);
	return (1);
}

void	put_sprite_to_window(t_game *game, void *sprite, int x, int y)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, sprite, x, y);
}

void	render_map(t_game *game)
{
	int (x), (y), (i), (j);
	i = -1;
	while (++i < game->mapdata->rows)
	{
		j = -1;
		while (++j <= game->mapdata->cols)
		{
			1 && (x = j * 64, y = i * 64);
			if (game->mapdata->map[i][j] == WALL)
				put_sprite_to_window(game, game->wall_sprite, x, y);
			else if (game->mapdata->map[i][j] == COLLECTIBLE)
				put_sprite_to_window(game, game->collectible_sprite, x, y);
			else if (game->mapdata->map[i][j] == EXIT)
				put_sprite_to_window(game, game->exit_sprite, x, y);
			else if (game->mapdata->map[i][j] == PLAYER)
				put_sprite_to_window(game, game->player, x, y);
			else if (game->mapdata->map[i][j] == EMPTY)
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
					game->floor_sprite, x, y);
			else if (game->mapdata->map[i][j] == ENEMY)
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
					game->enemy, x, y);
		}
	}
	
}

void	free_sprites(t_game *data)
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
	if (data->enemy)
		mlx_destroy_image(data->mlx_ptr, data->enemy);
}
