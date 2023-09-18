/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:52:58 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/18 10:29:30 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "../../includes/parsing.h"
#include "../../includes/message.h"
#include "../../libft/include/libft.h"

bool	elements_valid(t_map *map);
bool	undefined_element(char *line);
bool	player_pos_dup(t_map *map, char *line, int y);
bool	map_solvable(char **map, int x, int y, int height);

int	parsing_map_checks(t_map *map)
{
	char **check_map;

	if (!elements_valid(map))
		return (ERROR);
	check_map = ft_strs_copy((const char **)map->layout, map->height);
	if (!check_map)
		return (msg(NULL, strerror(errno), ERROR));
	if (!map_solvable(check_map, map->player_x, map->player_y, map->height))
	{
		ft_strs_free(check_map, map->height);
		return (ERROR);
	}
	ft_strs_free(check_map, map->height);
	return (EXIT_SUCCESS);
}

bool	elements_valid(t_map *map)
{
	int		i;

	i = 0;
	while (i++ < map->height)
	{
		if (undefined_element(map->layout[i]))
			return (msg(map->layout[i], ERR_INVALID_EL, false));;
		if (player_pos_dup(map, map->layout[i], i))
			return (msg(map->layout[i], ERR_PLAYER_DUP, false));
	}
	return (true);
}

bool	undefined_element(char *line)
{
	int	i;

	i = 0;
	while (i++ < ft_strlen(line[i]))
	{
		if (line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] != 'E'
			&& line[i] != ' ' && line[i] != '0' && line[i] != '1')
			return (msg(line, ERR_INVALID_EL, true));
	}
	return (false);
}

bool	player_pos_dup(t_map *map, char *line, int y)
{
	int	i;

	i = 0;
	while (i++ < ft_strlen(line[i]))
	{
		if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
			|| line[i] == 'E') && map->orientation == UNDEFINED)
		{
			map->player_x = i;
			map->player_y = y;
			if (line[i] == 'N')
				map->orientation = NORTH;
			if (line[i] == 'S')
				map->orientation = SOUTH;
			if (line[i] == 'E')
				map->orientation = EAST;
			if (line[i] == 'W')
				map->orientation = WEST;
		}
		else
			return (msg(line, ERR_PLAYER_DUP, true));
	}
	return (false);
}

// bool	map_solvable(char **map, int x, int y, int height)
// {
// 	if (map[y][x] == 'C' || map[y][x] == 'E' || map[y][x] == 'P' || \
// 		map[y][x] == '0')
// 	{
// 		map[y][x] = 'O';
// 		fill_path(map, x + 1, y);
// 		fill_path(map, x, y + 1);
// 		fill_path(map, x, y - 1);
// 		fill_path(map, x - 1, y);
// 	}
// 	return ;
// }
