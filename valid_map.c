/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:00:01 by tparratt          #+#    #+#             */
/*   Updated: 2024/03/14 14:22:29 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

static int	valid_character(t_map *map)
{
	size_t	i;
	size_t	j;
	char	*valid_character;

	i = 0;
	valid_character = "01CEP";
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (!ft_strchr(valid_character, map->map[i][j]))
			{
				ft_printf("\nError\nInvalid character\n\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	valid_shape(t_map *map)
{
	size_t		i;

	i = 0;
	while (map->map[i])
	{
		if ((ft_strlen(map->map[i]) - 1) != map->width)
		{
			ft_printf("\nError\nMap not rectangular\n\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	valid_ecp(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'E')
				map->e_count++;
			if (map->map[i][j] == 'C')
				map->c_count++;
			if (map->map[i][j] == 'P')
				map->p_count++;
			j++;
		}
		i++;
	}
	if (map->e_count != 1 || map->c_count < 1 || map->p_count != 1)
	{
		ft_printf("\nError\nInvalid number of E, C or P\n\n");
		return (1);
	}
	return (0);
}

static int	valid_walls(t_map *map)
{
	size_t	i;
	size_t	j;
	int		ret;

	i = 0;
	ret = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][++j])
		{
			if (i == 0 || i == map->depth || j == 0 || j == map->width)
			{
				if (map->map[i][j] != '1')
				{
					ret = 1;
					map->map[i][j] = '1';
				}
			}
		}
		i++;
	}
	if (ret == 1)
		ft_printf("\nError\nMap not surrounded by walls\n\n");
	return (ret);
}

int	valid_map(t_map *map)
{
	int	res1;
	int	res2;
	int	res3;
	int	res4;
	int	res5;

	res1 = valid_character(map);
	res2 = valid_shape(map);
	res3 = valid_ecp(map);
	res4 = valid_walls(map);
	res5 = valid_path(map);
	if (res1 == 1 || res2 == 1 || res3 == 1 || res4 == 1 || res5 == 1)
		return (1);
	return (0);
}
