/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:05:14 by aaugu             #+#    #+#             */
/*   Updated: 2023/10/10 14:40:20 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVEMENT_H
# define MOVEMENT_H

# include "cub3d.h"

/* ***********************************************************************	*/
/*							FUNCTIONS										*/
/* ***********************************************************************	*/

int	move_player(t_data *data);

int	move_player_forward(t_data *data);
int	move_player_backward(t_data *data);
int	move_player_right(t_data *data);
int	move_player_left(t_data *data);

int	rotate_player(t_data *data, double rotdir);

int	mouse_motion_handler(int x, int y, t_data *data);

#endif