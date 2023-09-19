/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/19 11:18:30 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/parsing.h"

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

// #include "../../libft/include/libft.h"
// #include <stdio.h>

// int	main(void)
// {
// 	t_map	map;

// 	map.width = 0;
// 	map.height = 0;
// 	map.player_x = -1;
// 	map.player_y = -1;
// 	map.orientation = UNDEFINED;
// 	map.east = NULL;
// 	map.north = NULL;
// 	map.west = NULL;
// 	map.south = NULL;
// 	map.f_color[0] = -1;
// 	map.f_color[1] = -1;
// 	map.f_color[2] = -1;
// 	map.c_color[0] = -1;
// 	map.c_color[1] = -1;
// 	map.c_color[2] = -1;
// 	map.layout = NULL;
// 	if (!parsing(&map, "../../maps/map_subject.cub"))
// 		printf("All went well.\n");
// 	else
// 		return (1);
// 	free(map.north);
// 	free(map.south);
// 	free(map.east);
// 	free(map.west);
// 	ft_strs_free(map.layout, map.height);
// 	return (0);
// }
