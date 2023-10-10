/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:55:22 by lvogt             #+#    #+#             */
/*   Updated: 2023/10/10 14:31:29 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "bonus.h"

int	check_pos(t_data *data, double pos_x, double pos_y);

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

int	check_pos(t_data *data, double pos_x, double pos_y)
{
	bool	test;

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
