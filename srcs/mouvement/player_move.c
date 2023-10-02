/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:55:22 by lvogt             #+#    #+#             */
/*   Updated: 2023/10/02 11:37:43 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "bonus.h"

int	check_pos(t_data *data, double pos_x, double pos_y)
{
	bool test;

	test = 0;
	if (pos_x > 0 && pos_x < data->map_width
		&& pos_y > 0 && pos_y < data->map_height)
		test = 1;
	if (BONUS)
	{
		if (data->map[(int)floor(pos_y)][(int)floor(pos_x)] == '1')
			test = 0;
	}
	return (test);
}

int	move_player_forward(t_data *data)
{
	double	pos_x;
	double	pos_y;

	pos_x = data->player.pos_x + data->player.dir_x * MOVESPEED;
	pos_y = data->player.pos_y + data->player.dir_y * MOVESPEED;
	if (check_pos(data, pos_x, pos_y))
	{
		data->player.pos_x = pos_x;
		data->player.pos_y = pos_y;
		return (1);
	}
	return (0);
}

int	move_player_backward(t_data *data)
{
	double	pos_x;
	double	pos_y;

	pos_x = data->player.pos_x - data->player.dir_x * MOVESPEED;
	pos_y = data->player.pos_y - data->player.dir_y * MOVESPEED;
	if (check_pos(data, pos_x, pos_y))
	{
		data->player.pos_x = pos_x;
		data->player.pos_y = pos_y;
		return (1);
	}
	return (0);
}

int	move_player_left(t_data *data)
{
	double	pos_x;
	double	pos_y;

	pos_x = data->player.pos_x + data->player.dir_y * MOVESPEED;
	pos_y = data->player.pos_y - data->player.dir_x * MOVESPEED;
	if (check_pos(data, pos_x, pos_y))
	{
		data->player.pos_x = pos_x;
		data->player.pos_y = pos_y;
		return (1);
	}
	return (0);
}

int	move_player_right(t_data *data)
{
	double	pos_x;
	double	pos_y;

	pos_x = data->player.pos_x - data->player.dir_y * MOVESPEED;
	pos_y = data->player.pos_y + data->player.dir_x * MOVESPEED;
	if (check_pos(data, pos_x, pos_y))
	{
		data->player.pos_x = pos_x;
		data->player.pos_y = pos_y;
		return (1);
	}
	return (0);
}

int	rotate_player(t_data *data)
{
	double x;
	double y;
	double O;

	O = ROTEDSPEED * data->player.rotate;
	x = data->player.dir_x;
	y = data->player.dir_y;
	data->player.dir_x = cos(O) * x - sin(O) * y;
	data->player.dir_y = cos(O) * y + sin(O) * x;
	x = data->player.plane_x;
	y = data->player.plane_y;
	data->player.plane_x = cos(O) * x - sin(O) * y;
	data->player.plane_y = cos(O) * y + sin(O) * x;
	return (1);
}

/* move_player:
 * modifi les données en fonction de l'ordre de déplacement reçu.
 * 
 * move_player :	data->player.pos_x/y	data->player.dir_x/y
 * rotate_player :	data->player.dir_x/y	data->player.plane_x/y 
 */
int	move_player(t_data *data)
{
	int	moved;
    (void) data;

	moved = 0;
	if (data->player.move_y == 1)
		moved += move_player_forward(data);
	if (data->player.move_y == -1)
		moved += move_player_backward(data);
	if (data->player.move_x == -1)
		moved += move_player_left(data);
	if (data->player.move_x == 1)
		moved += move_player_right(data);
	if (data->player.rotate != 0)
		moved += rotate_player(data);
	return (moved);
}

