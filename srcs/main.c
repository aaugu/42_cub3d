/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 09:29:21 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/21 11:45:56 by lvogt            ###   ########.fr       */
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
	printf(CYAN "\tesc" RESET ": close cub3D\n");
	if (BONUS)
		printf(CYAN "\tMouse" RESET ": rotate view\n");
	printf("\n");
}

int	key_press_handler(int key, t_data *data)
{
	if (key == MAINP_ESC)
		quit_cub3d(data);
	// if (key == MAINP_W)
	// 	data->player.move_y = 1;
	// if (key == MAINP_A)
	// 	data->player.move_x = -1;
	// if (key == MAINP_S)
	// 	data->player.move_y = -1;
	// if (key == MAINP_D)
	// 	data->player.move_x = 1;
	// if (key == ARROW_LEFT)
	// 	data->player.rotate -= 1;
	// if (key == ARROW_RIGHT)
	// 	data->player.rotate += 1;
	return (0);
}

int	key_release_handler(int key, t_data *data)
{
	if (key == MAINP_ESC)
		quit_cub3d(data);
	// if (key == MAINP_W && data->player.move_y == 1)
	// 	data->player.move_y = 0;
	// if (key == MAINP_A && data->player.move_x == -1)
	// 	data->player.move_x += 1;
	// if (key == MAINP_S && data->player.move_y == -1)
	// 	data->player.move_y = 0;
	// if (key == MAINP_D && data->player.move_x == 1)
	// 	data->player.move_x -= 1;
	// if (key == ARROW_LEFT && data->player.rotate <= 1)
	// 	data->player.rotate = 0;
	// if (key == ARROW_RIGHT && data->player.rotate >= -1)
	// 	data->player.rotate = 0;
	return (0);
}

void	listen_for_input(t_data *data)
{
	mlx_hook(data->win, ClientMessage, NoEventMask, quit_cub3d, data);
	mlx_hook(data->win, DestroyNotify, NoEventMask, quit_cub3d, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_press_handler, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release_handler, data);
	/*if (BONUS)
		mlx_hook(data->win, MotionNotify, PointerMotionMask,
			mouse_motion_handler, data);*/
}


/*
	data->texinfo.hex_floor = 0x8e8e8e;
	data->texinfo.hex_ceiling = 0x54C8E6;
	data->player.pos_x = (double)2 + 0.5;
	data->player.pos_y = (double)4 + 0.5;

	data->player.dir_x = 0;				// N : 	 0		S :	 0		E :	1		W :	-1
	data->player.dir_y = -1;			//		-1			 1			0			 0
	data->player.plane_x = 0.66;		//		 0.66		-0.66		0			 0
	data->player.plane_y = 0;			//		 0			 0			0.66		-0.66
	data->map_height = 5;
	data->map_width = 5;
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
	// mlx_loop_hook(data.mlx, render, &data);
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
