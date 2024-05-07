/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:36:34 by adesille          #+#    #+#             */
/*   Updated: 2024/05/07 13:17:17 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	change_fractal(t_coord **axis, keys_t key)
{
	if (key == 74)
		parse_coord(axis, (char *[3]){"a", "Julia", "1"});
	if (key == 75)
		parse_coord(axis, (char *[3]){"a", "Julia", "2"});
	if (key == 77)
		parse_coord(axis, (char *[3]){"a", "Mandelbrot"});
	store_instability(axis, (*axis)->zoom);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	static int	i = 0;
	t_data		*d;

	d = param;
	if (!(++i % 2))
	{
		if (keydata.key == 256)
			mlx_close_window(d->mlx);
		if (keydata.key == 262)
			rlshift_storage(d, 'l');
		if (keydata.key == 263)
			rlshift_storage(d, 'r');
		if (keydata.key == 264)
			dushift_storage(d, 'u');
		if (keydata.key == 265)
			dushift_storage(d, 'd');
		if (keydata.key >= 74 && keydata.key <= 77)
			change_fractal(&d->axis, keydata.key);
		put_pxl(d->image, &d->axis);
	}
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	static int	i;
	t_data	*d;
	double	time;

	d = param;
	mlx_get_mouse_pos(d->mlx, &d->axis->x_zoom, &d->axis->y_zoom);
	printf("zoom * %d = %f\nxdelta = %f\nydelta = %f\n", ++i, d->axis->zoom, xdelta, ydelta);
	if (ydelta == 1.)
		d->axis->zoom *= 0.9;
	else if (ydelta == -1.)
		d->axis->zoom *= 1.1;
	store_instability(&d->axis, d->axis->zoom);
	put_pxl(d->image, &d->axis);
}

// void	mouse_click(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
// {
// 	t_data	*d;

// 	d = param;
// 	if (button == MLX_MOUSE_BUTTON_MIDDLE)
// 	{
// 		store_instability(&d->axis, d->axis->zoom);
// 		put_pxl(d->image, &d->axis);
// 	}
// }

int	hook_init(t_data *d)
{
	mlx_scroll_hook(d->mlx, &scroll_hook, d);
	mlx_key_hook(d->mlx, &key_hook, d);
	// mlx_mouse_hook(d->mlx, &mouse_click, d);
	mlx_put_string(d->mlx, "Zoom : Scroll", 50, 50);
	mlx_put_string(d->mlx, "Move : Keyboard Arrows", 50, 70);
	mlx_put_string(d->mlx, "Change to Julia 1 : 'J'", 50, 90);
	mlx_put_string(d->mlx, "Change to Julia 2 : 'K'", 50, 110);
	mlx_put_string(d->mlx, "Change to Mandelbrot : 'M'", 50, 130);
	return (0);
}

////// TODO //////
/*
	-0- Pixel Incrementation
	-1- Graphics Optimization
		https://mandelbrowser.y0.pl/tutorial/computing.html#coloring
		https://www.youtube.com/watch?v=EbanExb75mc]
		-1.1- Change Colors every n times

	-2- Differents Sets
		-2.3- Nova Fractals sets
			- https://rotgers.io/posts/nova-fractals/
		-2.4- Phoenix
			https://www.jamesh.id.au/fractals/mandel/phoenix
	-3- Optimize Zoom & Shift 
		-3.2- Store every stable numbers, when zooming if (n root is the same == Stable)
		https://cglearn.eu/pub/advanced-computer-graphics/fractal-rendering
	-4- Color Shift
		https://cglearn.eu/pub/advanced-computer-graphics/fractal-rendering	
*/
/*
=== Today TODO ===

-3- Nova
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
				store_instability(&d->axis, d->axis->zoom);
				put_pxl(d->image, &axis);
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
