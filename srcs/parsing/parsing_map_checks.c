/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:52:58 by aaugu             #+#    #+#             */
/*   Updated: 2023/09/18 12:04:42 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "../../includes/parsing.h"
#include "../../includes/message.h"
#include "../../libft/include/libft.h"

bool	elements_valid(t_map *map);
bool	undefined_element(char *str);
bool	player_pos_dup(t_map *map, char *str, int y);
bool	map_solvable(char **map, int x, int y, int height);

int	parsing_map_checks(t_map *map)
{
	char	**check_map;

	if (!elements_valid(map))
		return (ERROR);
	// check_map = ft_strs_copy((const char **)map->layout, map->height);
	// if (!check_map)
	// 	return (msg(NULL, strerror(errno), ERROR));
	// if (!map_solvable(check_map, map->player_x, map->player_y, map->height))
	// {
	// 	ft_strs_free(check_map, map->height);
	// 	return (ERROR);
	// }
	// ft_strs_free(check_map, map->height);
	return (EXIT_SUCCESS);
}

bool	elements_valid(t_map *map)
{
	int		i;

	i = 0;
	while (i < map->height)
	{
		if (undefined_element(map->layout[i]))
			return (msg(map->layout[i], ERR_UNDEFINED, false));
		if (player_pos_dup(map, map->layout[i], i))
			return (msg(map->layout[i], ERR_PLAYER_DUP, false));
		i++;
	}
	return (true);
}

bool	undefined_element(char *str)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str))
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
	while (++i < ft_strlen(str))
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
