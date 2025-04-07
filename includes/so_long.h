/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:30:43 by moirhira          #+#    #+#             */
/*   Updated: 2025/04/07 22:58:40 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libraries/get_next_line/get_next_line.h"
# include "/usr/include/minilibx-linux/mlx.h"
# include "../libraries/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# define WALL '1'
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define EMPTY '0'

typedef struct s_vars
{
	int		var1;
	int		var2;
	int		var3;
	int		var4;
}			t_vars;

typedef struct s_data
{
	char	**map;
	int		rows;
	int		cols;
	int		player_count;
	int		exit_count;
	int		collectible_count;
	int		player_x;
	int		player_y;
}			t_data;

typedef struct s_game
{
	t_data	*mapdata;
	int		movement;
	int		score;
	void	*mlx;
	void	*win;
	void	*player_left;
	void	*player_right;
	void	*player_top;
	void	*player_dowwn;
	void	*player;
	void	*wall_sprite;
	void	*collectible_sprite;
	void	*exit_sprite;
	void	*floor_sprite;
}			t_game;

typedef struct s_accessibility
{
	int		colectibles_f;
	int		exit_f;
	int		**visited;
}			t_accessibility;

// validate map
void		fill_map_data(t_data **data);
int			chek_walls(t_data **data, int first_col_ln);
int			validate_map(t_data **data);
int			ft_strlen(char *str);
int			**allocate_visited_array(t_data *data);
int			check_accessibility(t_data *data);
int			validate_file_extension(char *file);
int			count_map_row(char *file);
char		**allocate_and_read_map(int rows, char *file);
int			read_map(t_data *new_map, char *file);

// main
int			load_spirets(t_game *game);
void		render_map(t_game *game);
void		free_sprites(t_game *data);
int			close_handler(t_game *data);
void		init_data(t_game *data);
int			init_main(t_game **gamedata, char *map);

#endif
