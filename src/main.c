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
#include "../includes/so_long.h"

void	update_game_state(t_game *data, int new_x, int new_y, int direction)
{
	if (data->mapdata->map[new_x][new_y] == 'C')
		printf("score : %d\n", ++data->score);
	else if (data->mapdata->map[new_x][new_y] == 'E')
	{
		if (data->mapdata->collectible_count == data->score)
			return ((void)(printf("You win!\n"), close_handler(data)));
		return ((void)(printf("You must collect all collectibles!\n")));
	}
	if (direction == 65361)
		data->player = data->player_left;
	else if (direction == 65363)
		data->player = data->player_right;
	else if (direction == 65362)
		data->player = data->player_top;
	else if (direction == 65364)
		data->player = data->player_dowwn;
	data->mapdata->map[data->mapdata->player_x][data->mapdata->player_y] = '0';
	data->mapdata->player_x = new_x;
	data->mapdata->player_y = new_y;
	data->mapdata->map[new_x][new_y] = 'P';
}

int	key_handler(int keycode, t_game *data)
{
	static int	movement = 0;

	int (new_x), (new_y);
	new_x = data->mapdata->player_x;
	new_y = data->mapdata->player_y;
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
	if (new_x >= 0 && new_x < data->mapdata->rows && new_y >= 0
		&& new_y < data->mapdata->cols
		&& data->mapdata->map[new_x][new_y] != '1')
	{
		update_game_state(data, new_x, new_y, keycode);
		1 && (movement++, printf("Movements: %d\n", movement));
	}
	else
		printf("Movement impossible!\n");
	return (1);
}

int	loop_hook(t_game *game)
{
	render_map(game);
	return (1);
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
