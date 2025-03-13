/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:48:23 by moirhira          #+#    #+#             */
/*   Updated: 2025/03/13 11:48:24 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/so_long_bonus.h"

void	accessibility(t_data *data, t_accessibility *state, int x, int y)
{
	if (x < 0 || x >= data->rows || y < 0 || y >= data->cols)
		return ;
	if (state->visited[x][y] || data->map[x][y] == WALL)
		return ;
	state->visited[x][y] = 1;
	if (data->map[x][y] == COLLECTIBLE)
		(*state->colectibles_f)++;
	if (data->map[x][y] == EXIT)
		(*state->exit_f)++;
	accessibility(data, state, x + 1, y);
	accessibility(data, state, x - 1, y);
	accessibility(data, state, x, y + 1);
	accessibility(data, state, x, y - 1);
}

int	**allocate_visited_array(t_data *data)
{
	int	**visited;

	int (i), (j);
	visited = malloc(data->rows * sizeof(int *));
	if (!visited)
	{
		printf("Error: Memory allocation failed!\n");
		return (0);
	}
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		visited[i] = malloc(sizeof(int) * data->cols);
		if (!visited[i])
			printf("Error: Memory allocation failed!\n");
		while (j < data->cols)
			visited[i][j++] = 0;
		i++;
	}
	return (visited);
}

int	check_accessibility(t_data *data)
{
	t_accessibility	state;
	int				**visited;

	int (clcbtl_f), (exit_f), (i);
	visited = allocate_visited_array(data);
	if (!visited || data->player_x == -1 || data->player_y == -1)
		return (0);
	clcbtl_f = 0;
	exit_f = 0;
	state.colectibles_f = &clcbtl_f;
	state.exit_f = &exit_f;
	state.visited = visited;
	accessibility(data, &state, data->player_x, data->player_y);
	i = -1;
	while (++i < data->rows)
		free(visited[i]);
	free(visited);
	if (clcbtl_f != data->collectible_count || !exit_f)
	{
		printf("Error : unaccessibility (exit OR collectibles)!\n");
		return (0);
	}
	return (1);
}
