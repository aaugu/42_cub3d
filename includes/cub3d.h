/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:54:01 by lvogt             #+#    #+#             */
/*   Updated: 2023/09/19 14:35:08 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "colors.h"
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

/* ***********************************************************************	*/
/*							MACRO											*/
/* ***********************************************************************	*/

// ERROR MESSAGES
# define ERR_USAGE "usage: ./cub3d <path/to/map.cub>"
# define ERR_MLX_START "Could not start mlx"
# define ERR_MLX_WIN "Could not create mlx window"
# define ERR_MLX_IMG "Could not create mlx image"
# define ERR_MALLOC "Could not allocate memory"

// Taille de la fenêtre
# define WIN_WIDTH 640
# define WIN_HEIGHT 480

// taille ttextures mures
# define TEX_SIZE 64

enum e_output
{
	SUCCESS,
	FAILURE,
	ERR,
	BREAK,
	CONTINUE
};

enum e_texture_index
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

/* ***********************************************************************	*/
/*							STRUCTURES										*/
/* ***********************************************************************	*/

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_texinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_texinfo;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_data
{
	void		*mlx;				//pointeur de l'affichage
	void		*win;				//pointeur de la fenetre
	int			win_height;			//lougeur de la fenetre
	int			win_width;			//hauteur de la fenetre
	int			map_height;			//longeur de la map
	int			map_width;			//hauteur de la map
	int			**textures;			//tableau de texture
	int			**texture_pixels;	//tableau des pixels pour les images
	char		**map;				//tableau pour la map
	t_texinfo	texinfo;			//info sur les textures
	t_player	player;				//info sur le player
	t_ray		ray;				//raycasting
}	t_data;

/* ***********************************************************************	*/
/*							FUNCTIONS										*/
/* ***********************************************************************	*/

/* exit/exit.c */
void	clean_exit(t_data *data, int code);
int		quit_cub3d(t_data *data);

/* exit/free_data.c */
void	free_tab(void **tab);
int		free_data(t_data *data);

/* init/init_data.c*/
void	init_data(t_data *data);
void	init_img_clean(t_img *img);
void	init_ray(t_ray *ray);
void	init_player(t_player *player);

/* init/init_mlx.c*/
void	init_mlx(t_data *data);
void	init_img(t_data *data, t_img *image, int width, int height);
void	init_texture_img(t_data *data, t_img *image, char *path);

/* init/init_texture.c*/
void	init_textures(t_data *data);
void	init_texinfo(t_texinfo *textures);

/* render/render.c */
void	render_images(t_data *data);

/* render/raycasting.c */
int		raycasting(t_player *player, t_data *data);

/* render/texture.c */
void	init_texture_pixels(t_data *data);
void	update_texture_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x);

/* error.c */
int		err_parsing_error(char *detail, char *str, int code);

#endif
