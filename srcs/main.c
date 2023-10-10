/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 09:29:21 by aaugu             #+#    #+#             */
/*   Updated: 2023/10/10 14:38:15 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "cub3d.h"
#include "key_macos.h"
#include "movement.h"
#include "listeners.h"

bool	extension_valid(const char *filename);

int	main(int ac, char **av)
{
	t_data	data;

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
