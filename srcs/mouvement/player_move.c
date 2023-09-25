/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:55:22 by lvogt             #+#    #+#             */
/*   Updated: 2023/09/21 14:07:46 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "bonus.h"

int	move_player(t_data *data)
{
	int	moved;
    (void) data;

	moved = 0;
	// if (data->player.move_y == 1)
	// 	moved += move_player_forward(data);
	// if (data->player.move_y == -1)
	// 	moved += move_player_backward(data);
	// if (data->player.move_x == -1)
	// 	moved += move_player_left(data);
	// if (data->player.move_x == 1)
	// 	moved += move_player_right(data);
	// if (data->player.rotate != 0)
	// 	moved += rotate_player(data);
	return (moved);
}