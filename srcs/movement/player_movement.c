/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:58:05 by aaugu             #+#    #+#             */
/*   Updated: 2023/10/10 14:43:08 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "movement.h"

/* move_player:
 * modifie les données en fonction de l'ordre de déplacement reçu.
 * 
 * move_player :	data->player.pos_x/y	data->player.dir_x/y
 * rotate_player :	data->player.dir_x/y	data->player.plane_x/y 
 */
int	move_player(t_data *data)
{
	int	moved;

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
