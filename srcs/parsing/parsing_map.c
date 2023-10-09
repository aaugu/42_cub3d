/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/10/06 16:10:10 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "parsing_map.h"
#include "bonus.h"
#include "libft.h"

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

int	init_parsing_map(t_map *map)
{
	map->orientation = UNDEFINED;
	map->east = NULL;
	map->north = NULL;
	map->west = NULL;
	map->south = NULL;
	map->layout = NULL;
	map->f_color[0] = -1;
	map->f_color[1] = -1;
	map->f_color[2] = -1;
	map->c_color[0] = -1;
	map->c_color[1] = -1;
	map->c_color[2] = -1;
	if (BONUS)
		map->valid_elements = ft_strdup("01 SEWND");
	else
		map->valid_elements = ft_strdup("01 SEWN");
	if (!map->valid_elements)
		return (parsing_error(map, NULL, strerror(errno), ERROR));
	if (BONUS)
		map->valid_env = ft_strdup("P0SEWN");
	else
		map->valid_env = ft_strdup("0SEWN");
	if (!map->valid_env)
		return (parsing_error(map, NULL, strerror(errno), ERROR));
	return (EXIT_SUCCESS);
}

void	parsing_map_free(t_map *map)
{
	if (map->south)
		free(map->south);
	if (map->east)
		free(map->east);
	if (map->west)
		free(map->west);
	if (map->north)
		free(map->north);
	if (map->valid_elements)
		free(map->valid_elements);
	if (map->valid_env)
		free(map->valid_env);
	if (map->layout)
		ft_strs_free(map->layout, map->height);
	map->east = NULL;
	map->north = NULL;
	map->west = NULL;
	map->south = NULL;
	map->layout = NULL;
	map->valid_elements = NULL;
	map->valid_env = NULL;
}
