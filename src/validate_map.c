/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <moirhira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:48:04 by moirhira          #+#    #+#             */
/*   Updated: 2025/04/11 16:29:28 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_doubled(char *str)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			counter++;
		i++;
	}
	if (counter > 1)
		return (1);
	return (0);
}

int	validate_file_extension(char *file)
{
	char	**fileval;

	if (is_doubled(file))
	{
		ft_printf("Error\nthe map have more than extension!\n");
		return (0);
	}
	fileval = ft_split(file, '.');
	if (ft_strcmp(fileval[0], "maps/") == 0 || ft_strcmp(fileval[0],
			"maps") == 0)
	{
		ft_printf("Error\nmissing map name!\n");
		free_split(fileval, ft_strlen_2d(fileval));
		return (0);
	}
	if (ft_strcmp(fileval[1], "ber") != 0)
	{
		ft_printf("Error\nBad extension!\n");
		free_split(fileval, ft_strlen_2d(fileval));
		return (0);
	}
	free_split(fileval, ft_strlen_2d(fileval));
	return (1);
}

int	count_map_row(char *file)
{
	char	*s;
	int		fd;
	int		rows;

	rows = 0;
	fd = open(file, O_RDONLY);
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		free(s);
		rows++;
	}
	close(fd);
	return (rows);
}

char	**allocate_and_read_map(int rows, char *file)
{
	char	*s;
	char	**map;
	int		fd;
	int		i;

	map = malloc((rows + 1) * sizeof(char *));
	if (!map)
		return (ft_printf("Error\nfrom malloc!\n"), NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nopening file!\n"), NULL);
	i = 0;
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		map[i++] = s;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int	read_map(t_data *new_map, char *file)
{
	int	i;
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nopening file\n"), 0);
	if (!validate_file_extension(file))
		return (0);
	new_map->rows = count_map_row(file);
	if (new_map->rows <= 0)
		return (ft_printf("Error\nmap empty!\n"), 0);
	new_map->map = allocate_and_read_map(new_map->rows, file);
	if (!new_map->map)
		return (0);
	fill_map_data(&new_map);
	if (!validate_map(&new_map) || !check_accessibility(new_map))
	{
		i = -1;
		while (++i < new_map->rows)
			free(new_map->map[i]);
		free(new_map->map);
		return (0);
	}
	return (1);
}
