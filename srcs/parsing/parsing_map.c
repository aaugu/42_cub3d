/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:55:53 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/11 12:02:58 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "parsing.h"
#include "libft.h"

t_map	parsing_map_infos(char *map_file)
{
	t_map	map;
	int		fd;
	int		count;
	char	*line;

	map = (t_map){0};
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (parsing_error(strerror, map_file, NULL));
	line = NULL;
	count = read_map(fd, &map);
	close(fd);
	if (count == 0)
		return (parsing_error("Map empty", map_file, NULL));
	return (map);
}
