/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:18:01 by tparratt          #+#    #+#             */
/*   Updated: 2024/03/20 10:37:56 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

int	init_map(t_map *map, char *map_buffer)
{
	map->map = ft_split(map_buffer, '\n');
	if (map->map == NULL)
		return (1);
	map->width = ft_strlen(map->map[0]) - 1;
	map->depth = 0;
	while (map->map[map->depth])
		map->depth++;
	map->depth = map->depth - 1;
	map->filled_map = alloc_to_zero(map);
	if (map->filled_map == NULL)
		return (1);
	map->e_count = 0;
	map->c_count = 0;
	map->p_count = 0;
	return (0);
}

void	free_map(t_map *map)
{
	size_t	i;

	i = 0;
	if (map->map != NULL)
	{
		free_split(map->map);
		map->map = NULL;
	}
	if (map->filled_map != NULL)
	{
		while (i < map->depth)
		{
			free(map->filled_map[i]);
			i++;
		}
		free(map->filled_map);
		map->filled_map = NULL;
	}
}

void	free_game(t_data *data)
{
	free_map(data->map);
	mlx_delete_image(data->mlx, data->background_img);
	mlx_delete_image(data->mlx, data->collectible_img);
	mlx_delete_image(data->mlx, data->exit_img);
	mlx_delete_image(data->mlx, data->player_img);
	mlx_delete_image(data->mlx, data->wall_img);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
		free(str[i--]);
	free(str);
}

size_t	**alloc_to_zero(t_map *map)
{
	size_t	i;
	size_t	j;
	size_t	**array;

	i = 0;
	array = malloc(sizeof(size_t) * map->depth);
	while (i < map->depth)
	{
		array[i] = malloc(sizeof(size_t) * map->width);
		if (array == NULL)
			return (NULL);
		i++;
	}
	i = 0;
	while (i < map->depth)
	{
		j = 0;
		while (j < map->width)
		{
			array[i][j] = 0;
			j++;
		}
		i++;
	}
	return (array);
}
