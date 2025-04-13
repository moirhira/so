/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:21:25 by moirhira          #+#    #+#             */
/*   Updated: 2025/04/11 16:29:07 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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
		free((*gamedata)->mapdata);
		free(*gamedata);
		return (0);
	}
	init_data(*gamedata);
	return (1);
}
