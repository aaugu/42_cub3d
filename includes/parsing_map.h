/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:00:22 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/19 13:03:16 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_MAP_H
# define PARSING_MAP_H

/******************************************************************************
*							      DEFINE									  *
******************************************************************************/

# define ERROR -1
# define STR_ERR_MAP "Map not valid"
# define ERR_NO_ARG "information argument is missing"
# define ERR_INFO_MISSING "information(s) missing"
# define ERR_INFO_DUP "information duplicate"
# define ERR_SEVERAL_ARGS "too many arguments on information"
# define ERR_NOT_NUM "argument not numerical"
# define ERR_ARG "invalid argument value"
# define ERR_UNDEFINED "undefined element in map"
# define ERR_PLAYER_DUP "should be only one player"
# define ERR_NOT_CLOSED "map not closed"

# define NO_ARG 0
# define SEVERAL_ARGS 1

/******************************************************************************
*							    	ENUM									  *
******************************************************************************/

typedef enum e_orientation
{
	NORTH,
	WEST,
	SOUTH,
	EAST,
	UNDEFINED,
}	t_orientation;

/******************************************************************************
*							    STRUCTURES									  *
******************************************************************************/

typedef struct s_map
{
	int				width;
	int				height;
	int				player_x;
	int				player_y;
	int				f_color[3];
	int				c_color[3];
	t_orientation	orientation;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			**layout;
}					t_map;

/******************************************************************************
*							    FUNCTIONS									  *
******************************************************************************/

void	init_map(t_map *map);
int		parsing_map(t_map *map, char *map_file);
void	parsing_map_free(t_map *map);
int		msg(char *arg, char *str, int exit_code);

int		parsing_map_infos(t_map *map, char *filename);
int		parsing_map_layout(t_map *map, char *filename, int map_position);
int		parsing_map_checks(t_map *map);

#endif
