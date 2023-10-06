/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <aaugu@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:24:59 by aaugu             #+#    #+#             */
/*   Updated: 2023/10/06 14:53:25 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mlx/mlx.h"

int test(void)
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 320, "Tutorial Window - Create Image");

    void *image = mlx_new_image(mlx, 64, 64);
    
    int pixel_bits;
	int line_bytes;
	int endian;
	int *buffer = (int *)mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);

	int color = 0xABCDEF;

	line_bytes /= 4;
	for(int y = 0; y < 64; ++y)
	{
		if (y % 2)
		{
			for(int x = 0; x < 64; ++x)
			{
				if (x % 2)
					buffer[(y * line_bytes) + x] = color;
			}
		}
	}

	mlx_put_image_to_window(mlx, win, image, 10, 10);

    mlx_loop(mlx);
	return (0);
}