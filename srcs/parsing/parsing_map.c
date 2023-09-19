/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/19 13:06:36 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing_map.h"

void	init_map(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->orientation = UNDEFINED;
	map->east = NULL;
	map->north = NULL;
	map->west = NULL;
	map->south = NULL;
	map->f_color[0] = -1;
	map->f_color[1] = -1;
	map->f_color[2] = -1;
	map->c_color[0] = -1;
	map->c_color[1] = -1;
	map->c_color[2] = -1;
	map->layout = NULL;
}

int	parsing_map(t_map *map, char *map_file)
{
	int	map_position;

	map_position = parsing_map_infos(map, map_file);
	if (map_position == ERROR)
		return (ERROR);
	if (parsing_map_layout(map, map_file, map_position) == ERROR)
		return (ERROR);
	if (parsing_map_checks(map) == ERROR)
		return (ERROR);
	return (EXIT_SUCCESS);
}

void	parsing_map_free(t_map *map)
{
	if (map->north)
		free(map->north);
	if (map->north)
		free(map->north);
	if (map->north)
		free(map->north);
	if (map->north)
		free(map->north);
	if (map->layout)
		free(map->north);
}
