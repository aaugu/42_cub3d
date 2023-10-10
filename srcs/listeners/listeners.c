/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listeners.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:28:26 by aaugu             #+#    #+#             */
/*   Updated: 2023/10/10 15:20:55 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_macos.h"
#include "cub3d.h"
#include "movement.h"
#include "bonus.h"
#include "listeners.h"

int		key_press_handler(int key, t_data *data);
int		key_release_handler(int key, t_data *data);
void	key_press_handler_bonus(int key, t_data *data, int x, int y);

/* listen_for_input:
 * quit cub3d si la fenêtre est fermée avec la croix ou esc
 * check si une touche voulue par le programme est pressée ou libérée.
 */
void	listen_for_input(t_data *data)
{
	mlx_hook(data->win, CLIENTMESSAGE, 0L, quit_cub3d, data);
	mlx_hook(data->win, DESTROYNOTIFY, 0L, quit_cub3d, data);
	mlx_hook(data->win, KEYPRESS, 1L << 0, key_press_handler, data);
	mlx_hook(data->win, KEYRELEASE, 1L << 1, key_release_handler, data);
	if (BONUS)
		mlx_hook(data->win, MOTIONNOTIFY, 1L << 6, mouse_motion_handler, data);
}

/* key_press_handler:
 * En fonction de la touche pressée, enregistre l'ordre de mouvement ou esc
 */
int	key_press_handler(int key, t_data *data)
{
	int	x;
	int	y;

	x = (int)floor(data->player.pos_x + data->player.dir_x);
	y = (int)floor(data->player.pos_y + data->player.dir_y);
	if (key == MAINP_ESC)
		quit_cub3d(data);
	if (key == MAINP_W)
		data->player.move_y = 1;
	if (key == MAINP_A)
		data->player.move_x = -1;
	if (key == MAINP_S)
		data->player.move_y = -1;
	if (key == MAINP_D)
		data->player.move_x = 1;
	if (key == ARROW_LEFT)
		data->player.rotate -= 1;
	if (key == ARROW_RIGHT)
		data->player.rotate += 1;
	if (BONUS)
		key_press_handler_bonus(key, data, x, y);
	return (0);
}

void	key_press_handler_bonus(int key, t_data *data, int x, int y)
{
	if (key == MAINP_M)
		data->minimap = !data->minimap;
	if (key == MAINP_SPACE)
	{
		if (data->map[y][x] == 'D' || data->map[y][x] == 'O')
			data->trigger = !data->trigger;
	}
}

/* key_release_handler:
 * En fonction de la touche libéré, remet l'ordre de mouvement à 0 ou esc
 */
int	key_release_handler(int key, t_data *data)
{
	if (key == MAINP_ESC)
		quit_cub3d(data);
	if (key == MAINP_W && data->player.move_y == 1)
		data->player.move_y = 0;
	if (key == MAINP_A && data->player.move_x == -1)
		data->player.move_x += 1;
	if (key == MAINP_S && data->player.move_y == -1)
		data->player.move_y = 0;
	if (key == MAINP_D && data->player.move_x == 1)
		data->player.move_x -= 1;
	if (key == ARROW_LEFT && data->player.rotate <= 1)
		data->player.rotate = 0;
	if (key == ARROW_RIGHT && data->player.rotate >= -1)
		data->player.rotate = 0;
	return (0);
}
