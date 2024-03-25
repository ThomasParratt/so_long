/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:13:23 by tparratt          #+#    #+#             */
/*   Updated: 2024/03/18 10:02:11 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

static int	read_init(char *map_buffer, char **argv, int file_len, t_map *map)
{
	int	fd;
	int	bytes_read;

	bytes_read = 0;
	fd = open(argv[1], O_RDONLY);
	bytes_read = read(fd, map_buffer, file_len);
	if (bytes_read <= 0)
	{
		ft_printf("\nError\nMap empty or cannot be read\n\n");
		free(map_buffer);
		return (1);
	}
	close(fd);
	if (init_map(map, map_buffer) == 1)
	{
		free(map_buffer);
		free_map(map);
		return (1);
	}
	free(map_buffer);
	return (0);
}

static int	get_file_len(char *arg)
{
	char	buffer[1];
	int		file_len;
	int		bytes_read;
	int		fd;

	bytes_read = 0;
	fd = open(arg, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("\nError\nCannot open file\n\n");
		exit(1);
	}
	while (read(fd, buffer, 1))
		bytes_read++;
	close(fd);
	file_len = bytes_read + 1;
	return (file_len);
}

static int	check_file_extension(char *arg)
{
	char	*ext;

	ext = ft_strchr(arg, '.');
	if (ext == NULL || ft_strncmp(ext, ".ber", 4) != 0)
	{
		ft_printf("\nError\nWrong file extension\n\n");
		return (1);
	}
	return (0);
}

static int	handle_arg(char *arg, char **argv)
{
	char	*map_buffer;
	int		file_len;
	t_map	map;

	if (check_file_extension(arg) == 1)
		return (1);
	file_len = get_file_len(arg);
	map_buffer = malloc(sizeof(char) * file_len);
	if (!map_buffer)
		return (1);
	if (read_init(map_buffer, argv, file_len, &map) == 1)
		return (1);
	if (valid_map(&map) == 1)
	{
		free_map(&map);
		return (1);
	}
	if (init_game(&map) == 1)
	{
		free_map(&map);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (handle_arg(argv[1], argv) == 1)
			return (1);
	}
	else
		ft_printf("\nError\nWrong number of arguments\n\n");
	return (0);
}
