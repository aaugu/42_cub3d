/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_infos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:32:26 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/11 14:59:20 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "parsing.h"

int	parsing_map_infos(t_map *map, char *filename)
{
	int				fd;
	t_state_machine	fsm;

	fsm = (t_state_machine){0};
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (msg(map, filename, strerror, EXIT_FAILURE));
	close(fd);
}

// int	get_line_infos(t_map *map, char *line)
// {
// 	if (ft_strncmp(line, "NO", 2))
// 		return (set_element(map, line, NORTH));
// 	if (ft_strncmp(line, "SO", 2))
// 		return (set_element(map, line, SOUTH));
// 	if (ft_strncmp(line, "WE", 2))
// 		return (set_element(map, line, WEST));
// 	if (ft_strncmp(line, "EA", 2))
// 		return (set_element(map, line, EAST));
// 	if (ft_strncmp(line, "F", 2))
// 		return (set_element(map, line, FLOOR));
// 	if (ft_strncmp(line, "C", 2))
// 		return (set_element(map, line, CEILING));
// }