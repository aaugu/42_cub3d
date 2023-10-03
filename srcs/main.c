/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 09:29:21 by aaugu             #+#    #+#             */
/*   Updated: 2023/10/03 14:33:08 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "cub3d.h"
#include "bonus.h"
#include "key_macos.h"

bool	extension_valid(const char *filename);

static void	print_controls(void)
{
	printf(PURPLE "\n");
	printf("                                    .--,-``-.                  \n");
	printf("  ,----..                  ,---,.  /   /     '.      ,---,     \n");
	printf(" /   /   \\         ,--,  ,'  .'  \\/ ../        ;   .'  .' `\\   \n");
	printf("|   :     :      ,'_ /|,---.' .' |\\ ``\\  .`-    ',---.'     \\  \n");
	printf(".   |  ;. / .--. |  | :|   |  |: | \\___\\/   \\   :|   |  .`\\  | \n");
	printf(".   ; /--`,'_ /| :  . |:   :  :  /      \\   :   |:   : |  '  | \n");
	printf(";   | ;   |  ' | |  . .:   |    ;       /  /   / |   ' '  ;  : \n");
	printf("|   : |   |  | ' |  | ||   :     \\      \\  \\   \\ '   | ;  .  | \n");
	printf(".   | '___:  | | :  ' ;|   |   . |  ___ /   :   ||   | :  |  ' \n");
	printf("'   ; : .'|  ; ' |  | ''   :  '; | /   /\\   /   :'   : | /  ;  \n");
	printf("'   | '/  :  | : ;  ; ||   |  | ; / ,,/  ',-    .|   | '` ,/   \n");
	printf("|   :    /'  :  `--'   \\   :   /  \\ ''\\        ; ;   :  .'     \n");
	printf(" \\   \\ .' :  ,      .-./   | ,'    \\   \\     .'  |   ,.'       \n");
	printf("  `---`    `--`----'   `----'       `--`-,,-'    '---'         \n");
	printf(RESET "\n");
	printf(CYAN "\tW" RESET ": move forward\t");
	printf(CYAN "\tS" RESET ": move backward\n");
	printf(CYAN "\tA" RESET ": strafe left\t");
	printf(CYAN "\tD" RESET ": strafe right\n");
	printf(CYAN "\t<" RESET ": rotate left\t");
	printf(CYAN "\t>" RESET ": rotate right\n");
	if (BONUS)
		printf(CYAN "\tMouse" RESET ": rotate view");
	printf(CYAN "\tesc" RESET ": close cub3D\n");
	printf("\n");
}

/* key_press_handler:
 * En fonction de la touche pressé, enregistre l'ordre de mouvement ou esc
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
	if (key == M)
		data->minimap = !data->minimap;
	if (key == MAINP_SPACE)
	{
		if (data->map[y][x] == 'D' || data->map[y][x] == 'O')
			data->trigger = !data->trigger;
	}
	return (0);
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

/* listen_for_input:
 * quit cub3d si la fenetre est fermé avec la croix ou esc
 * check si une touche voulu par le programme est pressé ou libéré.
 */
void	listen_for_input(t_data *data)
{
	mlx_hook(data->win, ClientMessage, NoEventMask, quit_cub3d, data);
	mlx_hook(data->win, DestroyNotify, NoEventMask, quit_cub3d, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_press_handler, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release_handler, data);
	if (BONUS)
		mlx_hook(data->win, MotionNotify, PointerMotionMask,
			mouse_motion_handler, data);
}

/*
	data->player.pos_x = (double)2 + 0.5;
	data->player.pos_y = (double)4 + 0.5;
	data->player.dir_x = 0;			// N : 	 0		S :	 0		E :	1		W :	-1
	data->player.dir_y = -1;		//		-1			 1			0			 0
	data->player.plane_x = 0.66;	//		 0.66		-0.66		0			 0
	data->player.plane_y = 0;		//		 0			 0			0.66		-0.66
*/
int	main(int ac, char **av)
{
	t_data	data;

	(void)av;
	if (ac != 2 || extension_valid(av[1]) == false)
		return (err_msg("Usage", ERR_USAGE, 1));
	init_data(&data);
	if (get_parsing_infos(&data, av[1]) == ERR)
		return (ERR);
	init_mlx(&data);
	init_textures(&data);
	print_controls();
	render_images(&data);
	listen_for_input(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}

bool	extension_valid(const char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strlen(extension) > 4)
		return (false);
	if (ft_strcmp(extension, ".cub") == 0)
		return (true);
	return (false);
}
