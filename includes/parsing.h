/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:56:46 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/15 17:05:15 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include "map.h"

/******************************************************************************
*							      DEFINE									  *
******************************************************************************/

# define ERROR -1
# define STR_ERR_MAP "Map not valid"
# define ERR_NO_ARG "information argument is missing"
# define ERR_INFO_MISSING "information(s) missing"
# define ERR_DUPLICATE "information duplicate"
# define ERR_SEVERAL_ARGS "too many arguments on information"
# define ERR_NOT_NUM "argument not numerical"
# define ERR_ARG "invalid argument"

/******************************************************************************
*							    	ENUM									  *
******************************************************************************/

typedef enum e_state
{
	idle,
	information,
	map_line,
	error,
	malloc_err,
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

// parsing base
int		parsing(t_map *map, char *map_file);
int		parsing_map_infos(t_map *map, char *filename);
int		parsing_map_layout(t_map *map, char *filename, int map_position);

//state machine
void	state_idle(t_state_machine *fsm, t_map *map, int position);
void	state_information(t_state_machine *fsm, t_map *map, int position);
void	state_map(t_state_machine *fsm, t_map *map);
void	set_texture(t_state_machine *fsm, char **element);
void	set_color(t_state_machine *fsm, int *element);
void	fsm_error(t_state_machine *fsm, t_state state, char *arg, char *str);

#endif
