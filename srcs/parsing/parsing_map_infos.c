/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_infos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:32:26 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/12 14:38:14 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../../includes/parsing.h"
#include "../../includes/message.h"
#include "../../libft/include/libft.h"

int		state_machine(t_map *map, int fd);
void	execute_state_machine(t_state_machine *fsm, t_map *map, int position);

int	parsing_map_infos(t_map *map, char *filename)
{
	int	fd;
	int	map_position;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (msg(filename, strerror(errno), EXIT_FAILURE));
	map_position = state_machine(map, fd);
	close(fd);
	return (map_position);
}

int	state_machine(t_map *map, int fd)
{
	int				i;
	t_state_machine	fsm;

	fsm = (t_state_machine){0};
	i = 1;
	while (true)
	{
		if (fsm.state == error || fsm.state == malloc_err)
			break ;
		else
		{
			fsm.line = get_next_line(fd);
			if (!fsm.line)
				break ;
			execute_state_machine(&fsm, map, i);
			free(fsm.line);
			i++;
		}
	}
	if (fsm.state == error)
		return (ERROR);
	if (fsm.state == malloc_err)
		return (msg(NULL, strerror(errno), ERROR));
	map->height = fsm.count_map_height;
	map->width = fsm.count_map_width;
	return (fsm.map_position);
}

void	execute_state_machine(t_state_machine *fsm, t_map *map, int position)
{
	if (fsm->state == idle)
		state_idle(fsm, map, position);
	else if (fsm->state == information)
		state_information(fsm, map, position);
	else if (fsm->state == map_line)
		state_map(fsm, map);
}
