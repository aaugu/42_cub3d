/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:56:46 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/11 14:45:17 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include "orientation.h"
# include "map.h"

/******************************************************************************
*							      DEFINE									  *
******************************************************************************/

# define ERROR -1
# define STR_ERR_MAP "Map not valid"

/******************************************************************************
*							    	ENUM									  *
******************************************************************************/

typedef enum e_state
{
	IDLE,
	NORTH,
	WEST,
	SOUTH,
	EAST,
	FLOOR,
	CEILING,
	NEWLINE,
	MAP_LINE,
}	t_state;

/******************************************************************************
*							    STRUCTURES									  *
******************************************************************************/

typedef struct s_state_machine
{
	t_state			state;
	bool			north;
	bool			south;
	bool			west;
	bool			east;
	bool			floor;
	bool			ceiling;
	int				count_map_width;
	int				count_map_height;
}					t_state_machine;

/******************************************************************************
*							    FUNCTIONS									  *
******************************************************************************/

int		parsing(t_map *map, char *map_file);

#endif