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

void	accessibility_c(t_data *data, t_accessibility *state, int x, int y)
{
	if (x < 0 || x >= data->rows || y < 0 || y >= data->cols)
		return ;
	if (state->visited[x][y] || data->map[x][y] == WALL
		|| data->map[x][y] == EXIT)
		return ;
	state->visited[x][y] = 1;
	if (data->map[x][y] == COLLECTIBLE)
		state->colectibles_f++;
	accessibility_c(data, state, x + 1, y);
	accessibility_c(data, state, x - 1, y);
	accessibility_c(data, state, x, y + 1);
	accessibility_c(data, state, x, y - 1);
}

void	accessibility_e(t_data *data, t_accessibility *state, int x, int y)
{
	if (x < 0 || x >= data->rows || y < 0 || y >= data->cols)
		return ;
	if (state->visited[x][y] || data->map[x][y] == WALL)
		return ;
	state->visited[x][y] = 1;
	if (data->map[x][y] == EXIT)
		state->exit_f++;
	accessibility_e(data, state, x + 1, y);
	accessibility_e(data, state, x - 1, y);
	accessibility_e(data, state, x, y + 1);
	accessibility_e(data, state, x, y - 1);
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
	int				i;

	visited = allocate_visited_array(data);
	if (!visited || data->player_x == -1 || data->player_y == -1)
		return (0);
	state.exit_f = 0;
	state.visited = visited;
	accessibility_e(data, &state, data->player_x, data->player_y);
	i = -1;
	while (++i < data->rows)
		free(visited[i]);
	free(visited);
	visited = allocate_visited_array(data);
	state.colectibles_f = 0;
	state.visited = visited;
	accessibility_c(data, &state, data->player_x, data->player_y);
	i = -1;
	while (++i < data->rows)
		free(visited[i]);
	free(visited);
	if (state.colectibles_f != data->collectible_count || !state.exit_f)
		return (printf("Err: unaccessibility (exit OR collectibles)!\n"), 0);
	return (1);
}
