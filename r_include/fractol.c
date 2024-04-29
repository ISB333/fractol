/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:36:34 by adesille          #+#    #+#             */
/*   Updated: 2024/04/29 14:53:52 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*d;

	d = param;
	if (keydata.key == 256)
		mlx_close_window(d->mlx);
	if (keydata.key == 262)
		d->axis->x_shift += 0.3 * d->axis->zoom;
	if (keydata.key == 263)
		d->axis->x_shift -= 0.3 * d->axis->zoom;
	if (keydata.key == 264)
		d->axis->y_shift += 0.3 * d->axis->zoom;
	if (keydata.key == 265)
		d->axis->y_shift -= 0.3 * d->axis->zoom;
	put_pxl(d->image, &d->axis, d->axis->zoom);
}

/*
-----------------------------------------
|                                       |
|         x,y                           |
|                                       |
|                                       |
|                                       |
|                                       |
|                                       |
|                                       |
|                                       |
|                                       |
|                                       |
-----------------------------------------
*/

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	static int i = 0;
	t_data	*d;

	d = param;
	mlx_get_mouse_pos(d->mlx, &d->axis->x_zoom, &d->axis->y_zoom);
	printf("zoom * %d = %f\nxdelta = %f\nydelta = %f\n", ++i, d->axis->zoom, xdelta, ydelta);
	printf("y mouse = %d\nx mouse = %d\n", d->axis->x_zoom, d->axis->y_zoom);
	d->axis->zoom *= 0.9;
	put_pxl(d->image, &d->axis, d->axis->zoom);
}

int	hook_init(t_data *d)
{
	mlx_scroll_hook(d->mlx, &scroll_hook, d);
	mlx_key_hook(d->mlx, &key_hook, d);
	return (0);
}

////// MANDATORY //////
/*
	-1- Zoom & Dezoom (following mouse)
		- Scroll 5%
		- Get x, y => new 0
	-2- Differents Sets
		-2.1- Julia Sets (Presets + argv given)
		-2.2- Nova Fractals sets
			- https://rotgers.io/posts/nova-fractals/
*/

int32_t	main(int argc, char *argv[])
{
	t_data	*d;
	t_coord	*axis;

	if (argc >= 2)
	{
		d = NULL;
		axis = NULL;
		if (parse_coord(&axis, argv))
		{
			if (init_img(&d))
			{
				d->axis = axis;
				hook_init(d);
				put_pxl(d->image, &axis, 1);
				if (mlx_image_to_window(d->mlx, d->image, 0, 0) == -1)
					return (mlx_close_window(d->mlx), error());		
				mlx_loop(d->mlx);
				mlx_delete_image(d->mlx, d->image);
				return (mlx_terminate(d->mlx), ff(d, axis), exit(EXIT_SUCCESS), 0);
			}
		}
		return (ff(d, axis), command_set("Invalid arguments !\n"), 1);
	}
	return (command_set("No arguments given !\n"), 0);
}

/*
================================ BONUS =================================
	-1- Window Management
		-2.2- Increase Window H/W by Window Size (mlx_resizefunc)
	-2- f(z) = sin(z) +c
		- https://rotgers.io/posts/sinz_fractal/
		- https://dev.to/freerangepixels/a-probably-terrible-way-to-render-gradients-1p3n
	-3- Parameters by arg given
		-3.1- If no or wrong parameters == quit and Show params available
	-4- Move View through Arrow Keys
	-5- Color Shift
*/
