/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:52:57 by tparratt          #+#    #+#             */
/*   Updated: 2024/03/15 14:27:58 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>

typedef struct s_map
{
	char	**map;
	size_t	**filled_map;
	size_t	width;
	size_t	depth;
	size_t	start_i;
	size_t	start_j;
	size_t	exit_i;
	size_t	exit_j;
	size_t	e_count;
	size_t	c_count;
	size_t	p_count;
}				t_map;

typedef struct s_data
{
	mlx_t		*mlx;
	t_map		*map;
	size_t		width;
	size_t		depth;
	int			block;
	size_t		pos_x;
	size_t		pos_y;
	mlx_image_t	*exit_img;
	mlx_image_t	*collectible_img;
	mlx_image_t	*player_img;
	mlx_image_t	*wall_img;
	mlx_image_t	*background_img;
	int			moves;
}				t_data;

int		valid_map(t_map *map);
int		valid_path(t_map *map);
void	free_split(char **str);
size_t	**alloc_to_zero(t_map *map);
void	player_hook(mlx_key_data_t keydata, t_data *data);
int		init_game(t_map *map);
void	free_game(t_data *data);
void	free_map(t_map *map);
int		init_map(t_map *map, char *map_buffer);

#endif