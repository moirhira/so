/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:26:52 by moirhira          #+#    #+#             */
/*   Updated: 2025/04/11 16:29:17 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	helper_game_state(t_game *data, int new_x, int new_y)
{
	if (!(new_x >= 0 && new_x < data->mapdata->rows && new_y >= 0
			&& new_y < data->mapdata->cols
			&& data->mapdata->map[new_x][new_y] != '1'))
		return (0);
	return (1);
}

int	update_game_state(t_game *data, int new_x, int new_y, int direction)
{
	if (!helper_game_state(data, new_x, new_y))
		return (0);
	else if (data->mapdata->map[new_x][new_y] == 'E')
	{
		if (data->mapdata->collectible_count == data->score)
			return (data->movement++, ft_printf("movement : %d\n",
					data->movement), close_handler(data), 0);
		return (0);
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
	int	new_x;
	int	new_y;

	new_x = data->mapdata->player_x;
	new_y = data->mapdata->player_y;
	if (keycode == 65307)
		close_handler(data);
	if (keycode == 65361 || keycode == 65363 || keycode == 65362
		|| keycode == 65364 || keycode == 119 || keycode == 115 || keycode == 97
		|| keycode == 100)
	{
		if (keycode == 65361 || keycode == 97)
			new_y--;
		else if (keycode == 65363 || keycode == 100)
			new_y++;
		else if (keycode == 65362 || keycode == 119)
			new_x--;
		else if (keycode == 65364 || keycode == 115)
			new_x++;
		if (update_game_state(data, new_x, new_y, keycode))
			ft_printf("movement : %d\n", data->movement);
		render_map(data);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_game	*gamedata;

	if (ac != 2)
		return (ft_printf("Error\nUsage: ./so_long  maps/<filename>\n"), 1);
	if (!init_main(&gamedata, av[1]))
		return (1);
	gamedata->mlx = mlx_init();
	if (!gamedata->mlx)
		return (ft_printf("Error\nmlx_init fail!\n"), close_handler(gamedata),
			1);
	gamedata->win = mlx_new_window(gamedata->mlx, 64 * gamedata->mapdata->cols,
			64 * gamedata->mapdata->rows, "Game : so_long");
	if (!gamedata->win)
		return (ft_printf("Error\ncreation window fail!\n"),
			close_handler(gamedata), 1);
	if (!load_spirets(gamedata))
		close_handler(gamedata);
	render_map(gamedata);
	mlx_hook(gamedata->win, 2, 1L << 0, key_handler, gamedata);
	mlx_hook(gamedata->win, 17, 0, close_handler, gamedata);
	mlx_loop(gamedata->mlx);
	close_handler(gamedata);
	return (0);
}
