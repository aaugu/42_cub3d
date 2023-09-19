/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:52:58 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/19 13:19:28 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include "parsing_map.h"
#include "libft.h"

bool	elements_valid(t_map *map);
bool	undefined_element(char *str);
bool	player_pos_dup(t_map *map, char *str, int y);
bool	map_closed(char **map, int x, int y);

int	parsing_map_checks(t_map *map)
{
	char	**check_map;

	if (!elements_valid(map))
		return (ERROR);
	check_map = ft_strs_copy((const char **)map->layout, map->height);
	if (!check_map)
		return (parsing_error(NULL, strerror(errno), ERROR));
	if (!map_closed(check_map, map->player_x, map->player_y))
	{
		ft_strs_free(check_map, map->height);
		return (parsing_error(STR_ERR_MAP, ERR_NOT_CLOSED, ERROR));
	}
	ft_strs_free(check_map, map->height);
	return (EXIT_SUCCESS);
}

bool	elements_valid(t_map *map)
{
	int		i;

	i = 0;
	while (i < map->height)
	{
		if (undefined_element(map->layout[i]))
			return (parsing_error(map->layout[i], ERR_UNDEFINED, false));
		if (player_pos_dup(map, map->layout[i], i))
			return (parsing_error(map->layout[i], ERR_PLAYER_DUP, false));
		i++;
	}
	return (true);
}

bool	undefined_element(char *str)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] != 'N' && str[i] != 'S' && str[i] != 'W' && str[i] != 'E'
			&& str[i] != ' ' && str[i] != '0' && str[i] != '1')
			return (true);
		i++;
	}
	return (false);
}

bool	player_pos_dup(t_map *map, char *str, int y)
{
	int	i;

	i = -1;
	while (++i < (int)ft_strlen(str))
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
		{
			if (map->orientation == UNDEFINED)
			{
				map->player_x = i;
				map->player_y = y;
				if (str[i] == 'N')
					map->orientation = NORTH;
				if (str[i] == 'S')
					map->orientation = SOUTH;
				if (str[i] == 'E')
					map->orientation = EAST;
				if (str[i] == 'W')
					map->orientation = WEST;
			}
			else
				return (true);
		}
	}
	return (false);
}

bool	map_closed(char **map, int x, int y)
{
	if (map[y][x] == ' ' )
		return (false);
	else if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || \
		map[y][x] == 'W' || map[y][x] == '0')
	{
		map[y][x] = 'A';
		if (!map_closed(map, x, y + 1))
			return (false);
		if (!map_closed(map, x, y - 1))
			return (false);
		if (!map_closed(map, x + 1, y))
			return (false);
		if (!map_closed(map, x - 1, y))
			return (false);
	}
	return (true);
}
