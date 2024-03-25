/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 09:55:18 by tparratt          #+#    #+#             */
/*   Updated: 2024/03/20 17:22:53 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

static int	is_valid_move(t_data *data, int x, int y)
{
	static size_t	temp;
	size_t			i;

	i = 0;
	if (data->map->map[x][y] == '1')
		return (1);
	else if (data->map->map[x][y] == 'C')
	{
		while (i < data->map->c_count)
		{
			if (data->collectible_img->instances[i].x == (y * data->block)
				&& data->collectible_img->instances[i].y == (x * data->block))
			{
				data->collectible_img->instances[i].x = -50;
				data->collectible_img->instances[i].y = -50;
				temp++;
			}
			i++;
		}
	}
	else if (data->map->map[x][y] == 'E' && temp == data->map->c_count)
		return (2);
	return (0);
}

static void	move_player(t_data *data, int x, int y)
{
	int	new_x;
	int	new_y;
	int	c_count;

	new_x = data->pos_x + x;
	new_y = data->pos_y + y;
	c_count = data->map->c_count;
	if (is_valid_move(data, new_x, new_y) == 0)
	{
		data->player_img->instances[0].x = new_y * data->block;
		data->player_img->instances[0].y = new_x * data->block;
		data->pos_x = new_x;
		data->pos_y = new_y;
		data->moves += 1;
		ft_printf("No. of moves: %d\n", data->moves);
	}
	else if (is_valid_move(data, new_x, new_y) == 2)
	{
		ft_printf("\nCONGRATULATIONS! You have reached the exit!\n\n");
		free_game(data);
		exit(0);
	}
}

void	player_hook(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_RIGHT)
			move_player(data, 0, 1);
		else if (keydata.key == MLX_KEY_LEFT)
			move_player(data, 0, -1);
		else if (keydata.key == MLX_KEY_UP)
			move_player(data, -1, 0);
		else if (keydata.key == MLX_KEY_DOWN)
			move_player(data, 1, 0);
		else if (keydata.key == MLX_KEY_ESCAPE)
		{
			free_game(data);
			exit(1);
		}
	}
}
