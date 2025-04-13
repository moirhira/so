/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:21:25 by moirhira          #+#    #+#             */
/*   Updated: 2025/04/11 16:35:10 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

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

void	init_data(t_game *data)
{
	data->movement = 0;
	data->score = 0;
	data->mlx = NULL;
	data->win = NULL;
	data->player_left = NULL;
	data->player_right = NULL;
	data->player_top = NULL;
	data->player_dowwn = NULL;
	data->player = NULL;
	data->wall_sprite = NULL;
	data->collectible_sprite = NULL;
	data->exit_sprite = NULL;
	data->floor_sprite = NULL;
	data->enemy = NULL;
}

void	render_moves(int movement, t_game *data)
{
	char	*str;
	char	*count;

	count = ft_itoa(movement);
	str = ft_strjoin("moves : ", count);
	mlx_string_put(data->mlx, data->win, 20, 20, 0xFFFFFF, str);
	free(count);
	free(str);
}
