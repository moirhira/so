/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:48:18 by moirhira          #+#    #+#             */
/*   Updated: 2025/04/11 16:29:20 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	fill_map_data(t_data **data)
{
	int	i;
	int	j;

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
	int	i;
	int	k;

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
					ft_printf("Error\nMap is not enclosed by walls!\n");
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
	int		i;
	int		j;

	i = 0;
	while (i < (*data)->rows)
	{
		j = 0;
		while (j < colslen)
		{
			c = (*data)->map[i][j];
			if (!(c == 'C' || c == '1' || c == 'E' || c == 'P' || c == '0'))
				return (ft_printf("Error\nInvalid character '%c' in map!\n", c),
					0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_objct_count(t_data **data)
{
	if ((*data)->player_count == 0)
		return (ft_printf("Error\nNo player!\n"), 0);
	if ((*data)->player_count != 1)
		return (ft_printf("Error\nDuplicate player!\n"), 0);
	if ((*data)->exit_count == 0)
		return (ft_printf("Error\nNo exit!\n"), 0);
	if ((*data)->exit_count != 1)
		return (ft_printf("Error\nDuplicate exit!\n"), 0);
	if ((*data)->collectible_count < 1)
		return (ft_printf("Error\nNo enough collectibles!\n"), 0);
	return (1);
}

int	validate_map(t_data **data)
{
	int	i;
	int	first_col_ln;
	int	len;

	first_col_ln = ft_strlen((*data)->map[0]) - 1;
	i = 0;
	while (++i < (*data)->rows)
	{
		len = ft_strlen((*data)->map[i]);
		if ((*data)->map[i][len - 1] == '\n')
			len--;
		if (len != first_col_ln)
			return (ft_printf("Error\nNo rectangular!\n"), 0);
	}
	(*data)->cols = first_col_ln;
	if (!chek_walls(data, first_col_ln))
		return (0);
	if (!only_valid_chars(data, first_col_ln))
		return (0);
	if (!check_objct_count(data))
		return (0);
	return (1);
}
