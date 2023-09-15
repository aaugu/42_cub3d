/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_layout.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:32:38 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/15 16:48:34 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../../includes/parsing.h"
#include "../../includes/message.h"
#include "../../libft/include/libft.h"

int		fill_map(t_map *map, int map_position, int fd);
void	fill_with_void(char *map_line, int size, int width);

int	parsing_map_layout(t_map *map, char *filename, int map_position)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (msg(filename, strerror(errno), ERROR));
	map->layout = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!map->layout)
		return (msg(NULL, strerror(errno), ERROR));
	map->layout[map->height] = NULL;
	if (fill_map(map, map_position, fd) == ERROR)
		return (ERROR);
	// if (check_map(map->layout) == ERROR)
	// 	return (ERROR);
	return (EXIT_SUCCESS);
}

int	fill_map(t_map *map, int map_position, int fd)
{
	int		i;
	int		size;
	char	*line;

	i = 1;
	while (i < map_position)
	{
		get_next_line(fd);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		map->layout[i] = (char *)malloc(sizeof(char) * (map->width));
		if (!map)
			return (msg(NULL, strerror(errno), ERROR));
		map->layout[i][map->width] = '\0';
		line = get_next_line(fd);
		if (!line)
			return (msg(NULL, strerror(errno), ERROR));
		size = ft_strlcpy(map->layout[i], line, map->width);
		if (size - 1 < map->width)
			fill_with_void(map->layout[i], size - 1, map->width);
		free(line);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	fill_with_void(char *map_line, int size, int width)
{
	int	i;

	i = size;
	while (i < width)
	{
		map_line[i] = ' ';
		i++;
	}
}

// int	main(void)
// {
// 	t_map	map;
// 	int		i = 0;

// 	map.width = 33;
// 	map.height = 14;
// 	map.player[0] = 0;
// 	map.player[1] = 0;
// 	map.orientation = UNDEFINED;
// 	map.layout = NULL;
// 	parsing_map_layout(&map, "map_subject.cub", 9);
// 	while (i++ < map.height)
// 		printf("%sEOL\n", map.layout[i]);
// 	return (0);
// }
