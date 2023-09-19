/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_state_machine.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:56:46 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/19 12:56:31 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_STATE_MACHINE_H
# define PARSING_STATE_MACHINE_H

# include "parsing_map.h"

/******************************************************************************
*							      DEFINE									  *
******************************************************************************/

# define ERROR -1

/******************************************************************************
*							    	ENUM									  *
******************************************************************************/

typedef enum e_state
{
	idle,
	information,
	map_line,
	error,
}	t_state;

/******************************************************************************
*							    STRUCTURES									  *
******************************************************************************/

typedef struct s_state_machine
{
	t_state	state;
	char	*line;
	int		info_count;
	int		count_map_width;
	int		count_map_height;
	int		map_position;
}					t_state_machine;

/******************************************************************************
*							    FUNCTIONS									  *
******************************************************************************/

void	state_idle(t_state_machine *fsm, t_map *map);
void	state_information(t_state_machine *fsm, t_map *map, int position);
void	state_map(t_state_machine *fsm);
void	set_texture(t_state_machine *fsm, char **element);
void	set_color(t_state_machine *fsm, int *element);
void	fsm_error(t_state_machine *fsm, t_state state, char *arg, char *str);

#endif
