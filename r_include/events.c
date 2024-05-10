/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:57:01 by adesille          #+#    #+#             */
/*   Updated: 2024/05/10 13:59:17 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


void	change_fractal(t_data **d, keys_t key)
{
	if (key == 74)
		init_set(&(*d)->axis, (char *[3]){"a", "Julia", "1"});
	if (key == 75)
		init_set(&(*d)->axis, (char *[3]){"a", "Julia", "2"});
	if (key == 76)
		init_set(&(*d)->axis, (char *[3]){"a", "Julia", "3"});
	if (key == 77)
		init_set(&(*d)->axis, (char *[3]){"a", "Mandelbrot"});
	if (key == 66)
		init_set(&(*d)->axis, (char *[3]){"b", "Burning"});
	put_pxl((*d)->image, &(*d)->axis, (*d)->axis->zoom);
}

void	change_color(t_data **d, keys_t key)
{
	if (key == 320)
		(*d)->axis->colormode = 'g';
	else if (key == 321)
		(*d)->axis->colormode = 's';
	else if (key == 322)
		(*d)->axis->colormode = 'z';
	else if (key == 323)
		(*d)->axis->colormode = 'n';
	else if (key == 323)
		(*d)->axis->colormode = 'm';
	put_pxl((*d)->image, &(*d)->axis, (*d)->axis->zoom);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	static int	i;
	t_data		*d;

	d = param;
	if (!(++i % 2))
	{
		if (keydata.key == 256)
			mlx_close_window(d->mlx);
		if ((keydata.key >= 74 && keydata.key <= 77) || keydata.key == 66)
			change_fractal(&d, keydata.key);
		if (keydata.key >= 320 && keydata.key <= 329)
			change_color(&d, keydata.key);
		else
		{
			if (keydata.key == 262)
				rlshift_storage(d, 'l');
			if (keydata.key == 263)
				rlshift_storage(d, 'r');
			if (keydata.key == 264)
				dushift_storage(d, 'u');
			if (keydata.key == 265)
				dushift_storage(d, 'd');
			shift_put_pxl(d->image, &d->axis);
		}
	}
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	static int	i;
	t_data		*d;

	d = param;
	mlx_get_mouse_pos(d->mlx, &d->axis->x_zoom, &d->axis->y_zoom);
	printf("zoom * %d = %f\nxdelta = %f\nydelta = %f\n", ++i, d->axis->zoom, xdelta, ydelta);
	if (ydelta == 1.)
		d->axis->zoom *= 0.8;
	else if (ydelta == -1.)
		d->axis->zoom *= 1.2;
	put_pxl(d->image, &d->axis, d->axis->zoom);
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
	return (0);
}