/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:52:58 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/19 14:26:47 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include "parsing_map.h"
#include "bonus.h"
#include "libft.h"

bool	elements_valid(t_map *map, char *valid_elements);
bool	undefined_element(char *str, char *valid_elements);
bool	player_pos_dup(t_map *map, char *str, int y);
bool	map_closed(char **map, int x, int y, char *valid_env);

int	parsing_map_checks(t_map *map)
{
	char	**check_map;

	if (!elements_valid(map, map->valid_elements))
		return (ERROR);
	check_map = ft_strs_copy((const char **)map->layout, map->height);
	if (!check_map)
		return (parsing_error(NULL, strerror(errno), ERROR));
	if (!map_closed(check_map, map->player_x, map->player_y, map->valid_env))
	{
		ft_strs_free(check_map, map->height);
		return (parsing_error(STR_ERR_MAP, ERR_NOT_CLOSED, ERROR));
	}
	ft_strs_free(check_map, map->height);
	return (EXIT_SUCCESS);
}

bool	elements_valid(t_map *map, char *valid_elements)
{
	int		i;

	i = 0;
	while (i < map->height)
	{
		if (undefined_element(map->layout[i], valid_elements))
			return (parsing_error(map->layout[i], ERR_UNDEFINED, false));
		if (player_pos_dup(map, map->layout[i], i))
			return (parsing_error(map->layout[i], ERR_PLAYER_DUP, false));
		i++;
	}
	return (true);
}

bool	undefined_element(char *str, char *valid_elements)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(str))
	{
		if (strchr(valid_elements, str[i]))
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
		if (strchr("SEWN", str[i]))
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

bool	map_closed(char **map, int x, int y, char *valid_env)
{
	if (map[y][x] == ' ' )
		return (false);
	else if (strchr(valid_env, map[y][x]))
	{
		map[y][x] = 'A';
		if (!map_closed(map, x, y + 1, valid_env))
			return (false);
		if (!map_closed(map, x, y - 1, valid_env))
			return (false);
		if (!map_closed(map, x + 1, y, valid_env))
			return (false);
		if (!map_closed(map, x - 1, y, valid_env))
			return (false);
	}
	return (true);
}
