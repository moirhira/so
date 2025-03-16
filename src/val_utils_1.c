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
#include "../includes/so_long.h"

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
		while (k < first_col_ln)
		{
			if (i == 0 || i == (*data)->rows - 1 || k == 0 || k == first_col_ln
				- 1)
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

int	only_valid_chars(t_data **data, int colslen)
{
	char	c;

	int (i), (j);
	i = 0;
	while (i < (*data)->rows)
	{
		j = 0;
		while (j < colslen)
		{
			c = (*data)->map[i][j];
			if (!(c == 'C' || c == '1' || c == 'E' || c == 'P' || c == '0'))
				return (printf("Error: Invalid character '%c' in map!\n", c),
					0);
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_data **data)
{
	int (i), (first_col_ln), (len);
	if ((*data)->rows == 0)
		return (printf("Eroor : map empty!\n"), 0);
	first_col_ln = ft_strlen((*data)->map[0]) - 1;
	if (!only_valid_chars(data, first_col_ln))
		return (0);
	i = 0;
	while (++i < (*data)->rows)
	{
		len = ft_strlen((*data)->map[i]);
		if ((*data)->map[i][len - 1] == '\n')
			len--;
		if (len != first_col_ln)
			return (printf("Error: Map is not rectangular!\n"), 0);
	}
	(*data)->cols = first_col_ln;
	if (!chek_walls(data, first_col_ln))
		return (0);
	if ((*data)->player_count != 1 || (*data)->exit_count != 1
		|| (*data)->collectible_count < 1)
	{
		printf("invalid mapp!\n");
		return (0);
	}
	return (1);
}
