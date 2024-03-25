/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:31:33 by tparratt          #+#    #+#             */
/*   Updated: 2024/03/15 15:20:53 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

static size_t	valid_position(t_map *map, size_t i, size_t j)
{
	if (j > map->width)
		return (0);
	if (map->map[i][j] == '1')
		return (0);
	if (map->filled_map[i][j] == 1)
		return (0);
	return (1);
}

static void	fill_if_valid(t_map *map, size_t i, size_t j)
{
	if (!valid_position(map, i, j))
		return ;
	map->filled_map[i][j] = 1;
	fill_if_valid(map, i - 1, j);
	fill_if_valid(map, i + 1, j);
	fill_if_valid(map, i, j - 1);
	fill_if_valid(map, i, j + 1);
}

static void	get_start_and_exit(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'P')
			{
				map->start_i = i;
				map->start_j = j;
			}
			if (map->map[i][j] == 'E')
			{
				map->exit_i = i;
				map->exit_j = j;
			}
			j++;
		}
		i++;
	}
}

int	valid_path(t_map *map)
{
	size_t	i;
	size_t	j;

	get_start_and_exit(map);
	fill_if_valid(map, map->start_i, map->start_j);
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'C' || map->map[i][j] == 'E')
			{
				if (!map->filled_map[i][j])
				{
					ft_printf("\nError\nNo valid path\n\n");
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}
