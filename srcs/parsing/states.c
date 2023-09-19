/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:54:27 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/19 09:59:00 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../libft/include/libft.h"

bool	is_empty_line(char *str);
void	start_map(t_state_machine *fsm, int position);

void	state_idle(t_state_machine *fsm, t_map *map)
{
	if (!ft_strncmp(fsm->line, "NO ", 3))
		set_texture(fsm, &map->north);
	else if (!ft_strncmp(fsm->line, "SO ", 3))
		set_texture(fsm, &map->south);
	else if (!ft_strncmp(fsm->line, "WE ", 3))
		set_texture(fsm, &map->west);
	else if (!ft_strncmp(fsm->line, "EA ", 3))
		set_texture(fsm, &map->east);
	else if (!ft_strncmp(fsm->line, "F ", 2))
		set_color(fsm, map->f_color);
	else if (!ft_strncmp(fsm->line, "C ", 2))
		set_color(fsm, map->c_color);
	else if (is_empty_line(fsm->line) == true)
		return ;
	else
		fsm_error(fsm, error, STR_ERR_MAP, ERR_INFO_MISSING);
}

void	state_information(t_state_machine *fsm, t_map *map, int position)
{
	if (fsm->info_count < 6)
	{
		if (!ft_strncmp(fsm->line, "NO ", 3))
			set_texture(fsm, &map->north);
		else if (!ft_strncmp(fsm->line, "SO ", 3))
			set_texture(fsm, &map->south);
		else if (!ft_strncmp(fsm->line, "WE ", 3))
			set_texture(fsm, &map->west);
		else if (!ft_strncmp(fsm->line, "EA ", 3))
			set_texture(fsm, &map->east);
		else if (!ft_strncmp(fsm->line, "F ", 2))
			set_color(fsm, map->f_color);
		else if (!ft_strncmp(fsm->line, "C ", 2))
			set_color(fsm, map->c_color);
		else if (is_empty_line(fsm->line) == true)
			return ;
		else
			fsm_error(fsm, error, STR_ERR_MAP, ERR_INFO_MISSING);
	}
	else if ((is_empty_line(fsm->line) == true))
		return ;
	else if (fsm->info_count == 6)
		start_map(fsm, position);
}

void	start_map(t_state_machine *fsm, int position)
{
	fsm->state = map_line;
	fsm->map_position = position;
	fsm->count_map_height++;
	fsm->count_map_width = ft_strlen(fsm->line);
}

void	state_map(t_state_machine *fsm)
{
	if (is_empty_line(fsm->line) == true)
		fsm_error(fsm, error, STR_ERR_MAP, ERR_NOT_CLOSED);
	else
	{
		fsm->count_map_height++;
		if ((int)ft_strlen(fsm->line) > fsm->count_map_width)
			fsm->count_map_width = ft_strlen(fsm->line);
	}
}

bool	is_empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n')
		i++;
	if (i == (int)ft_strlen(str))
		return (true);
	return (false);
}
