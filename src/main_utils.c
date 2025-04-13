/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:47:55 by moirhira          #+#    #+#             */
/*   Updated: 2025/04/11 16:29:14 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	load_spirets(t_game *game)
{
	int	width;
	int	height;

	game->player_left = mlx_xpm_file_to_image(game->mlx,
			"spiretes/player_left.xpm", &height, &width);
	game->player_right = mlx_xpm_file_to_image(game->mlx,
			"spiretes/player_right.xpm", &height, &width);
	game->player_top = mlx_xpm_file_to_image(game->mlx,
			"spiretes/player_top.xpm", &height, &width);
	game->player_dowwn = mlx_xpm_file_to_image(game->mlx,
			"spiretes/player_down.xpm", &height, &width);
	game->player = game->player_right;
	game->wall_sprite = mlx_xpm_file_to_image(game->mlx, "spiretes/wall.xpm",
			&height, &width);
	game->collectible_sprite = mlx_xpm_file_to_image(game->mlx,
			"spiretes/collectible.xpm", &height, &width);
	game->exit_sprite = mlx_xpm_file_to_image(game->mlx, "spiretes/exit.xpm",
			&height, &width);
	game->floor_sprite = mlx_xpm_file_to_image(game->mlx, "spiretes/floor.xpm",
			&height, &width);
	if (!game->player_left || !game->player_right || !game->collectible_sprite
		|| !game->wall_sprite || !game->exit_sprite || !game->floor_sprite
		|| !game->player_dowwn || !game->player_top)
		return (ft_printf("Error\nfailed load sprites!\n"), 0);
	return (1);
}

void	put_win(t_game *game, void *sprite, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, sprite, x, y);
}

void	render_map(t_game *game)
{
	t_vars	vars;

	vars.var1 = -1;
	while (++vars.var1 < game->mapdata->rows)
	{
		vars.var2 = -1;
		while (++vars.var2 <= game->mapdata->cols)
		{
			vars.var3 = vars.var2 * 64;
			vars.var4 = vars.var1 * 64;
			if (game->mapdata->map[vars.var1][vars.var2] == WALL)
				put_win(game, game->wall_sprite, vars.var3, vars.var4);
			else if (game->mapdata->map[vars.var1][vars.var2] == COLLECTIBLE)
				put_win(game, game->collectible_sprite, vars.var3, vars.var4);
			else if (game->mapdata->map[vars.var1][vars.var2] == EXIT)
				put_win(game, game->exit_sprite, vars.var3, vars.var4);
			else if (game->mapdata->map[vars.var1][vars.var2] == PLAYER)
				put_win(game, game->player, vars.var3, vars.var4);
			else if (game->mapdata->map[vars.var1][vars.var2] == EMPTY)
				put_win(game, game->floor_sprite, vars.var3, vars.var4);
		}
	}
}

void	free_sprites(t_game *data)
{
	if (data->player_left)
		mlx_destroy_image(data->mlx, data->player_left);
	if (data->player_right)
		mlx_destroy_image(data->mlx, data->player_right);
	if (data->player_top)
		mlx_destroy_image(data->mlx, data->player_top);
	if (data->player_dowwn)
		mlx_destroy_image(data->mlx, data->player_dowwn);
	if (data->collectible_sprite)
		mlx_destroy_image(data->mlx, data->collectible_sprite);
	if (data->wall_sprite)
		mlx_destroy_image(data->mlx, data->wall_sprite);
	if (data->exit_sprite)
		mlx_destroy_image(data->mlx, data->exit_sprite);
	if (data->floor_sprite)
		mlx_destroy_image(data->mlx, data->floor_sprite);
}

int	close_handler(t_game *data)
{
	int	i;

	free_sprites(data);
	if (data->mapdata)
	{
		i = 0;
		while (i < data->mapdata->rows)
		{
			free(data->mapdata->map[i]);
			i++;
		}
		free(data->mapdata->map);
	}
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->mapdata);
	free(data);
	exit(0);
}
