/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:36:34 by adesille          #+#    #+#             */
/*   Updated: 2024/04/19 16:34:00 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
	- MLX_init();
	- MLX_put_pixels();
		- Transform Pixel Value into complex Plame
			- complex_calc();
				- shaders_render();
	- ff();
*/

int32_t	main(void)
{
	t_data	*d;

	d = malloc(sizeof(t_data));
	d->mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
	if (!d->mlx)
		error();
	d->image = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->image)
        return (mlx_close_window(d->mlx), error());

	put_pxl(0, 0, d->image);
	if (mlx_image_to_window(d->mlx, d->image, 0, 0))
        return (mlx_close_window(d->mlx), error());
	
	mlx_loop(d->mlx);
	mlx_terminate(d->mlx);
	return (EXIT_SUCCESS);
}