/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/11 14:54:30 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing.h"
#include "message.h"
#include "libft.h"

int		parsing_error(t_map *map, char *arg, char *str, int exit_code);
void	parsing_free(t_map *map);

int	parsing(t_map *map, char *map_file)
{
	int				fd;
	int				map_position;

	map_position = parsing_map_infos(map, map_position);
	if (map_position == ERROR)
		return (parsing_error(map, NULL, NULL, EXIT_FAILURE));
	map->layout = malloc(sizeof(char *) * (map->height + 1));
	if (!map->layout)
		return (parsing_error(map, NULL, strerror, EXIT_FAILURE));
	if (parsing_map_layout(map, map_position) == ERROR)
		return (parsing_error(map, NULL, strerror, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	parsing_error(t_map *map, char *arg, char *str, int exit_code)
{
	if (str)
		msg(arg, str, exit_code);
	parsing_free(map);
}

void	parsing_free(t_map *map)
{
	if (map->north)
		free(map->north);
	if (map->south)
		free(map->south);
	if (map->west)
		free(map->west);
	if (map->east)
		free(map->east);
	if (map->layout)
		ft_strs_free(map->layout, map->height);
}

