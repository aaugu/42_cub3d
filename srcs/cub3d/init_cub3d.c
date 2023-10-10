/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvogt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:44:12 by aaugu             #+#    #+#             */
/*   Updated: 2023/10/06 15:02:21 by lvogt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "parsing_map.h"
#include "cub3d.h"
#include "libft.h"

// int				get_parsing_infos(t_data *data, char *filename);
int				get_textures(t_texinfo *textures, t_map *map);
unsigned long	convert_rgb_to_hex(int	*rgb);
void			get_player_orientation(t_player *player, int orientation);
void			get_player_orientation_2(t_player *player, int orientation);

// int	init_game(t_data *data, char *filename)
// {
// 	init_data(data);
// 	if (get_parsing_infos(data, filename) == ERR)
// 		return (ERR);
// 	init_mlx(data);
// 	init_textures(data);
// 	return (SUCCESS);
// }

int	get_parsing_infos(t_data *data, char *filename)
{
	t_map	map;

	if (init_parsing_map(&map) == ERROR)
		return (ERR);
	if (parsing_map(&map, filename) == ERROR)
		return (ERR);
	data->map_height = map.height;
	data->map_width = map.width;
	data->map = ft_strs_copy((const char **)map.layout, map.height);
	if (!data->map)
		return (parsing_error(&map, NULL, strerror(errno), errno));
	data->player.pos_x = (double) map.player_x + 0.5;
	data->player.pos_y = (double) map.player_y + 0.5;
	data->sprite.x = data->player.pos_x;
	data->sprite.y = data->player.pos_y;
	data->map[map.player_y][map.player_x] = '0';
	get_player_orientation(&data->player, map.orientation);
	if (get_textures(&data->texinfo, &map))
		return (ERR);
	parsing_map_free(&map);
	return (SUCCESS);
}

int	get_textures(t_texinfo *textures, t_map *map)
{
	textures->south = ft_strdup(map->south);
	if (!textures->south)
		return (parsing_error(map, map->south, strerror(errno), errno));
	textures->east = ft_strdup(map->east);
	if (!textures->east)
		return (parsing_error(map, map->east, strerror(errno), errno));
	textures->west = ft_strdup(map->west);
	if (!textures->west)
		return (parsing_error(map, map->west, strerror(errno), errno));
	textures->north = ft_strdup(map->north);
	if (!textures->north)
		return (parsing_error(map, map->north, strerror(errno), errno));
	textures->hex_floor = convert_rgb_to_hex(map->f_color);
	textures->hex_ceiling = convert_rgb_to_hex(map->c_color);
	return (EXIT_SUCCESS);
}

unsigned long	convert_rgb_to_hex(int	*rgb)
{
	return (((rgb[0] & 0xff) << 16) + ((rgb[1] & 0xff) << 8) + (rgb[2] & 0xff));
}

void	get_player_orientation(t_player *player, int orientation)
{
	if (orientation == SOUTH)
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (orientation == NORTH)
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else
		get_player_orientation_2(player, orientation);
}

void	get_player_orientation_2(t_player *player, int orientation)
{
	if (orientation == WEST)
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else if (orientation == EAST)
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
}
