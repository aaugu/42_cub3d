/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/18 11:02:23 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "../../includes/parsing.h"
#include "../../includes/message.h"
#include "../../libft/include/libft.h"

int		parsing_error(t_map *map, char *arg, char *str, int exit_code);
void	parsing_free(t_map *map);

int	parsing(t_map *map, char *map_file)
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

int	main(void)
{
	t_map	map;

	map.width = 0;
	map.height = 0;
	map.player_x = -1;
	map.player_y = 0;
	map.orientation = UNDEFINED;
	map.east = NULL;
	map.north = NULL;
	map.west = NULL;
	map.south = NULL;
	map.f_color[0] = -1;
	map.f_color[1] = -1;
	map.f_color[2] = -1;
	map.c_color[0] = -1;
	map.c_color[1] = -1;
	map.c_color[2] = -1;
	map.layout = NULL;
	parsing(&map, "../../maps/map_subject.cub");
	return (0);
}
