/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:55:22 by lvogt             #+#    #+#             */
/*   Updated: 2023/10/03 11:08:48 by lvogt            ###   ########.fr       */
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
		if (data->map[(int)floor(pos_y)][(int)floor(pos_x)] > '0'
			&& data->map[(int)floor(pos_y)][(int)floor(pos_x)] != 'O')
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

int	rotate_player(t_data *data, double rotdir)
{
	double x;
	double y;
	double O;

	O = ROTEDSPEED * rotdir;
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

void	wrap_mouse_position(t_data *data, int x, int y)
{
	if (x > data->win_width - DIST_EDGE_MOUSE_WRAP)
	{
		x = DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(data->win, x, y);
	}
	if (x < DIST_EDGE_MOUSE_WRAP)
	{
		x = data->win_width - DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(data->win, x, y);
	}
}

int	mouse_motion_handler(int x, int y, t_data *data)
{
	static int	old_x = WIN_WIDTH / 2;

	wrap_mouse_position(data, x, y);
	if (x == old_x)
		return (0);
	else if (x < old_x)
		data->player.moved += rotate_player(data, -1);
	else if (x > old_x)
		data->player.moved += rotate_player(data, 1);
	old_x = x;
	return (0);
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
		moved += rotate_player(data, data->player.rotate);
	return (moved);
}

