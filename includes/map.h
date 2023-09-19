/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:00:22 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/18 09:43:50 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

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

#endif
