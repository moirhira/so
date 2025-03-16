/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:21:25 by moirhira          #+#    #+#             */
/*   Updated: 2025/03/14 20:21:34 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/so_long_bonus.h"

int	close_handler(t_game *data)
{
	int (i);
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
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free(data->mapdata);
	free(data);
	exit(0);
}
