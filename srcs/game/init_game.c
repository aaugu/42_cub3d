/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:44:12 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/19 15:42:05 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_map.h"
#include "cub3d.h"

int	init_game(char *filename, )
{
	t_map	map;

	if (init_parsing_map(&map) == ERROR)
		return (ERR);
	if (parsing_map(&map, filename) == ERROR)
		return (parsing_error(&map, NULL, NULL, ERR));

	parsing_map_free(&map);
	return (SUCCESS);
}

