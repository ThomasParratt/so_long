/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:31:54 by tparratt          #+#    #+#             */
/*   Updated: 2024/03/20 10:36:32 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

static void	display_image(mlx_t *mlx, t_data *data, mlx_image_t *img, char pos)
{
	size_t	i;
	size_t	j;
	int		block;

	i = 0;
	block = data->block;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (data->map->map[i][j] == pos)
			{
				if (mlx_image_to_window(mlx, img, j * block, i * block) < 0)
				{
					free_game(data);
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
}

static mlx_image_t	*new_background_image(mlx_t *mlx, t_data *data, char *file)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(file);
	if (!texture)
	{
		free_map(data->map);
		exit(1);
	}
	else
	{
		img = mlx_texture_to_image(mlx, texture);
		mlx_delete_texture(texture);
		if (!img)
		{
			free_game(data);
			exit(1);
		}
		display_image(mlx, data, img, '0');
		display_image(mlx, data, img, 'P');
		display_image(mlx, data, img, 'C');
		display_image(mlx, data, img, 'E');
		mlx_resize_image(img, data->block, data->block);
	}
	return (img);
}

static mlx_image_t	*new_image(mlx_t *mlx, t_data *data, char *file, char pos)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(file);
	if (!texture)
	{
		free_map(data->map);
		exit(1);
	}
	else
	{
		img = mlx_texture_to_image(mlx, texture);
		mlx_delete_texture(texture);
		if (!img)
		{
			free_game(data);
			exit(1);
		}
		display_image(mlx, data, img, pos);
		mlx_resize_image(img, data->block, data->block);
	}
	return (img);
}

static void	init_data(t_map *map, t_data *data)
{
	data->map = map;
	data->block = 40;
	data->width = (map->width + 1) * data->block;
	data->depth = (map->depth + 1) * data->block;
	if (data->width > 2520 || data->depth > 1320)
	{
		ft_printf("\nError\nMap too large for display\n\n");
		free_map(map);
		exit(1);
	}
	data->pos_x = data->map->start_i;
	data->pos_y = data->map->start_j;
	data->moves = 0;
}

int	init_game(t_map *map)
{
	mlx_t		*mlx;
	t_data		data;

	init_data(map, &data);
	mlx = mlx_init(data.width, data.depth, "so_long", true);
	if (!mlx)
		return (1);
	data.mlx = mlx;
	data.background_img = new_background_image(mlx, &data, "textures/blue.png");
	data.wall_img = new_image(mlx, &data, "textures/wall.png", '1');
	data.exit_img = new_image(mlx, &data, "textures/yellow.png", 'E');
	data.player_img = new_image(mlx, &data, "textures/smiley.png", 'P');
	data.collectible_img = new_image(mlx, &data, "textures/pizza.png", 'C');
	mlx_key_hook(mlx, (mlx_keyfunc) player_hook, &data);
	mlx_loop(mlx);
	free_game(&data);
	return (0);
}
