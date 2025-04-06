/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:47:47 by moirhira          #+#    #+#             */
/*   Updated: 2025/03/13 11:47:49 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/so_long_bonus.h"

int	update_game_state(t_game *data, int new_x, int new_y, int direction)
{
	if (!(new_x >= 0 && new_x < data->mapdata->rows && new_y >= 0
		&& new_y < data->mapdata->cols
		&& data->mapdata->map[new_x][new_y] != '1'))
		return (0);
	else if (data->mapdata->map[new_x][new_y] == 'X')
		return (printf("You lose!\n"), close_handler(data), 0);
	else if (data->mapdata->map[new_x][new_y] == 'E')
	{
		if (data->mapdata->collectible_count == data->score)
			return (printf("You win!\n"), close_handler(data), 0);
		return (printf("You must collect all collectibles!\n"), 0);
	}
	data->movement++;
	if (data->mapdata->map[new_x][new_y] == 'C')
		data->score++;
	if (direction == 65361 || direction == 97)
		data->player = data->player_left;
	else if (direction == 65363 || direction == 100)
		data->player = data->player_right;
	else if (direction == 65362 || direction == 119)
		data->player = data->player_top;
	else if (direction == 65364 || direction == 115)
		data->player = data->player_dowwn;
	data->mapdata->map[data->mapdata->player_x][data->mapdata->player_y] = '0';
	data->mapdata->player_x = new_x;
	data->mapdata->player_y = new_y;
	data->mapdata->map[new_x][new_y] = 'P';
	return (1);
}

int	key_handler(int keycode, t_game *data)
{
	int new_x;
	int new_y;
	new_x = data->mapdata->player_x;
	new_y = data->mapdata->player_y;
	if (keycode == 65307)
		close_handler(data);
	if (keycode == 65361 || keycode == 65363 || keycode == 65362 || keycode == 65364 || 
		keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
	{
		if (keycode == 65361 || keycode == 97)
			new_y--;
		else if (keycode == 65363 || keycode == 100)
			new_y++;
		else if (keycode == 65362 || keycode == 119)
			new_x--;
		else if (keycode == 65364 || keycode == 115)
			new_x++;
		update_game_state(data, new_x, new_y, keycode);
	}
	return (1);
}

int	loop_hook(t_game *game)
{
	render_map(game);
	render_moves(game->movement,game);
	return (1);
}

void init_data(t_game *data)
{
	data->movement = 0;
	data->score = 0;
	data->mlx_ptr = NULL;
	data->win_ptr  = NULL;
	data->player_left  = NULL;
	data->player_right  = NULL;
	data->player_top  = NULL;
	data->player_dowwn  = NULL;
	data->player  = NULL;
	data->wall_sprite  = NULL;
	data->collectible_sprite  = NULL;
	data->exit_sprite  = NULL;
	data->floor_sprite  = NULL;
	data->enemy  = NULL;
}
int	init_main(t_game **gamedata, char *map)
{
	*gamedata = malloc(sizeof(t_game));
	if (!*gamedata)
		return (0);
	(*gamedata)->mapdata = malloc(sizeof(t_data));
	if (!(*gamedata)->mapdata)
	{
		free(*gamedata);
		return (0);
	}
	
	if (!read_map((*gamedata)->mapdata, map))
	{
		printf("map problem!\n");
		free((*gamedata)->mapdata);
		free(*gamedata);
		return (0);
	}
	init_data(*gamedata);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	*gamedata;

	if (ac != 2)
	{
		printf("%s\n", "Usage: %s <filename>\n");
		return (0);
	}
	if (!init_main(&gamedata, av[1]))
		return (0);
	gamedata->mlx_ptr = mlx_init();
	if (!gamedata->mlx_ptr)
		return (0);
	
	gamedata->win_ptr = mlx_new_window(gamedata->mlx_ptr, 64
			* gamedata->mapdata->cols, 64 * gamedata->mapdata->rows,
			"Game : race");
	if (!gamedata->win_ptr)
		return (free(gamedata->mlx_ptr), 1);
	if (!load_spirets(gamedata))
		close_handler(gamedata);
	mlx_hook(gamedata->win_ptr, 2, 1L << 0, key_handler, gamedata);
	mlx_hook(gamedata->win_ptr, 17, 0, close_handler, gamedata);
	mlx_loop_hook(gamedata->mlx_ptr, loop_hook, gamedata);
	mlx_loop(gamedata->mlx_ptr);
	close_handler(gamedata);
	return (1);
}
