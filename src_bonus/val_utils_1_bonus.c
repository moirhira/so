/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:48:18 by moirhira          #+#    #+#             */
/*   Updated: 2025/03/13 11:48:19 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/so_long_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	fill_map_data(t_data **data)
{
	int (i), (j);
	(*data)->player_count = 0;
	(*data)->exit_count = 0;
	(*data)->collectible_count = 0;
	i = -1;
	while (++i < (*data)->rows)
	{
		j = 0;
		while ((*data)->map[i][j] != '\0')
		{
			if ((*data)->map[i][j] == COLLECTIBLE)
				(*data)->collectible_count++;
			if ((*data)->map[i][j] == PLAYER)
			{
				(*data)->player_count++;
				(*data)->player_x = i;
				(*data)->player_y = j;
			}
			if ((*data)->map[i][j] == EXIT)
				(*data)->exit_count++;
			j++;
		}
	}
}

int	chek_walls(t_data **data, int first_col_ln)
{
	int (i), (k);
	i = 0;
	while (i < (*data)->rows)
	{
		k = 0;
		while (k < first_col_ln - 1)
		{
			if (i == 0 || i == (*data)->rows - 1 || k == 0 || k == first_col_ln
				- 2)
			{
				if ((*data)->map[i][k] != WALL)
				{
					printf("Error: Map is not enclosed by walls!\n");
					return (0);
				}
			}
			k++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_data **data)
{
	int (i), (first_col_ln), (len);
	if ((*data)->rows == 0)
	{
		printf("Eroor : map empty!\n");
		return (0);
	}
	first_col_ln = ft_strlen((*data)->map[0]);
	i = 0;
	while (++i <= (*data)->rows - 1)
	{
		len = ft_strlen((*data)->map[i]);
		if (len != first_col_ln)
			return (printf("Error: Map is not rectangular!\n"), 0);
	}
	(*data)->cols = first_col_ln - 1;
	chek_walls(data, first_col_ln);
	if ((*data)->player_count != 1 || (*data)->exit_count != 1
		|| (*data)->collectible_count < 1)
	{
		printf("invalid mapp!\n");
		return (0);
	}
	return (1);
}
