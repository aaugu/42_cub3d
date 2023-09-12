/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:54:27 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/12 14:40:07 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/parsing.h"
#include "../../libft/include/libft.h"

void	start_map(t_state_machine *fsm, int position);

void	state_idle(t_state_machine *fsm, t_map *map, int position)
{
	if (ft_strncmp(fsm->line, "NO ", 3))
		set_texture(&fsm->state, fsm->line, &map->north);
	else if (ft_strncmp(fsm->line, "SO ", 3))
		set_texture(&fsm->state, fsm->line, &map->south);
	else if (ft_strncmp(fsm->line, "WE ", 3))
		set_texture(&fsm->state, fsm->line, &map->west);
	else if (ft_strncmp(fsm->line, "EA ", 3))
		set_texture(&fsm->state, fsm->line, &map->east);
	else if (ft_strncmp(fsm->line, "F ", 2))
		set_colors(&fsm->state, fsm->line, &map->f_color);
	else if (ft_strncmp(fsm->line, "C ", 2))
		set_colors(fsm->state, fsm->line, &map->c_color);
	else if (is_empty_line(fsm->line) == true)
		return ;
	else
		fsm_error(&fsm->state, error, STR_ERR_MAP, ERR_INFO_MISSING);
}

void	state_information(t_state_machine *fsm, t_map *map, int position)
{
	if (fsm->info_count < 6)
	{
		if (ft_strncmp(fsm->line, "NO ", 3))
			set_texture(&fsm->state, fsm->line, &map->north);
		else if (ft_strncmp(fsm->line, "SO ", 3))
			set_texture(&fsm->state, fsm->line, &map->south);
		else if (ft_strncmp(fsm->line, "WE ", 3))
			set_texture(&fsm->state, fsm->line, &map->west);
		else if (ft_strncmp(fsm->line, "EA ", 3))
			set_texture(&fsm->state, fsm->line, &map->east);
		else if (ft_strncmp(fsm->line, "F ", 2))
			set_colors(&fsm->state, fsm->line, &map->f_color);
		else if (ft_strncmp(fsm->line, "C ", 2))
			set_colors(fsm->state, fsm->line, &map->c_color);
		else if (is_empty_line(fsm->line) == true)
			return ;
		else
			fsm_error(&fsm->state, error, STR_ERR_MAP, ERR_INFO_MISSING);
	}
	else if ((is_empty_line(fsm->line) == true))
		return ;
	if (fsm->info_count == 6)
		start_map(fsm, position);
}

void	start_map(t_state_machine *fsm, int position)
{
	fsm->state = map_line;
	fsm->map_position = position;
	fsm->count_map_height++;
	fsm->count_map_width = ft_strlen(fsm->line);
}

void	state_map(t_state_machine *fsm, t_map *map)
{
	if (is_empty_line(fsm->line) == true)
		fsm_error(&fsm->state, error, STR_ERR_MAP, "Map not closed");
	else
	{
		fsm->count_map_height++;
		if (ft_strlen(fsm->line) > fsm->count_map_width)
			fsm->count_map_width = ft_strlen(fsm->line);
	}
}
