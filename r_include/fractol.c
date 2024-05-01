/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:36:34 by adesille          #+#    #+#             */
/*   Updated: 2024/05/01 12:04:21 by isb3             ###   ########.fr       */
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
		d->axis->y_shift -= 0.3 * d->axis->zoom;
	if (keydata.key == 265)
		d->axis->y_shift += 0.3 * d->axis->zoom;
	put_pxl(d->image, &d->axis, d->axis->zoom);
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	static int	i = 0;
	t_data	*d;

	d = param;
	mlx_get_mouse_pos(d->mlx, &d->axis->x_zoom, &d->axis->y_zoom);
	printf("zoom * %d = %f\nxdelta = %f\nydelta = %f\n", ++i, d->axis->zoom, xdelta, ydelta);
	if (ydelta == 1.)
		d->axis->zoom *= 0.9;
	else if (ydelta == -1.)
		d->axis->zoom *= 1.1;
	put_pxl(d->image, &d->axis, d->axis->zoom);
}

int	hook_init(t_data *d)
{
	mlx_scroll_hook(d->mlx, &scroll_hook, d);
	mlx_key_hook(d->mlx, &key_hook, d);
	return (0);
}

////// TODO //////
/*
	-1- Graphics
		-1.1- Optimizing
		https://cglearn.eu/pub/advanced-computer-graphics/fractal-rendering	

	-2- Differents Sets
		-2.1- Julia Sets (Presets + argv given)
		-2.2- Nova Fractals sets
			- https://rotgers.io/posts/nova-fractals/
	-3- Optimize Zoom & Shift 
		-3.1- Tile Rendering for shifting
		-3.2- Store every stable numbers, when zooming if (n root is the same == Stable)
		https://cglearn.eu/pub/advanced-computer-graphics/fractal-rendering
	-4- Color Shift
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
				printf("AAAAAAAA\n");
				d->axis = axis;
				hook_init(d);
				put_pxl(d->image, &axis, 1);
				if (mlx_image_to_window(d->mlx, d->image, 0, 0) == -1)
					return (mlx_close_window(d->mlx), error());
				mlx_loop(d->mlx);
				mlx_delete_image(d->mlx, d->image);
				return (mlx_terminate(d->mlx), ff(d, axis, 0), 0);
			}
		}
		return (command_set("Invalid arguments !\n"), ff(d, axis, 1), 1);
	}
	return (command_set("No arguments given !\n"), 0);
}
