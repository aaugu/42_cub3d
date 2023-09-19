/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_infos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:32:26 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/19 12:58:10 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include "parsing_map.h"
#include "parsing_state_machine.h"
#include "libft.h"

int		state_machine(t_map *map, int fd);
void	init_state_machine(t_state_machine *fsm);
void	execute_state_machine(t_state_machine *fsm, t_map *map, int position);

int	parsing_map_infos(t_map *map, char *filename)
{
	int	fd;
	int	map_position;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (msg(filename, strerror(errno), ERROR));
	map_position = state_machine(map, fd);
	close(fd);
	return (map_position);
}

int	state_machine(t_map *map, int fd)
{
	t_state_machine	fsm;
	int				i;

	init_state_machine(&fsm);
	i = 1;
	while (fsm.state != error && fsm.state != malloc_err)
	{
		fsm.line = get_next_line(fd);
		if (!fsm.line)
			break ;
		execute_state_machine(&fsm, map, i);
		free(fsm.line);
		i++;
	}
	if (fsm.state == error || fsm.state == malloc_err)
		return (ERROR);
	map->height = fsm.count_map_height;
	map->width = fsm.count_map_width - 1;
	return (fsm.map_position);
}

void	init_state_machine(t_state_machine *fsm)
{
	fsm->state = idle;
	fsm->info_count = 0;
	fsm->count_map_height = 0;
	fsm->count_map_width = 0;
	fsm->map_position = -1;
	fsm->line = NULL;
}

void	execute_state_machine(t_state_machine *fsm, t_map *map, int position)
{
	if (fsm->state == idle)
		state_idle(fsm, map);
	else if (fsm->state == information)
		state_information(fsm, map, position);
	else if (fsm->state == map_line)
		state_map(fsm);
}

void	fsm_error(t_state_machine *fsm, t_state state, char *arg, char *str)
{
	fsm->state = state;
	if (str)
		msg(arg, str, EXIT_FAILURE);
}
