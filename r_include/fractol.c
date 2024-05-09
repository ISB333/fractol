/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:11:42 by isb3              #+#    #+#             */
/*   Updated: 2024/05/09 15:29:19 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:36:34 by adesille          #+#    #+#             */
/*   Updated: 2024/05/08 12:50:51by isb3             ###   ########.fr       */
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
		(*d)->axis->colormode = 'n';
	put_pxl((*d)->image, &(*d)->axis, (*d)->axis->zoom);
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
	t_data	*d;

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

void	show_commands()
{
	ft_putstr_fd("\n░▒▓████████▓▒░▒▓███████▓▒░ ░▒▓██████▓▒░ ░▒▓██████▓▒░▒▓██████\
██▓▒░▒▓██████▓▒░░▒▓█▓▒░        \n\
░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░  ░▒▓█▓▒░\
░▒▓█▓▒░▒▓█▓▒░        \n\
░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░        ░▒▓█▓▒░  ░▒▓█▓▒░\
░▒▓█▓▒░▒▓█▓▒░        \n\
░▒▓██████▓▒░ ░▒▓███████▓▒░░▒▓████████▓▒░▒▓█▓▒░        ░▒▓█▓▒░  ░▒▓█▓▒░\
░▒▓█▓▒░▒▓█▓▒░        \n\
░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░        ░▒▓█▓▒░  ░▒▓█▓▒░\
░▒▓█▓▒░▒▓█▓▒░        \n\
░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▒░  ░▒▓█▓▒░\
░▒▓█▓▒░▒▓█▓▒░        \n\
░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░  ░▒▓█▓▒░   ░▒▓██████▓▒░\
░▒▓████████▓▒░ \n\n", 1);
	ft_putstr_fd("Zoom : Scroll\n", 1);
	ft_putstr_fd("Move : Keyboard Arrows\n\n", 1);
	ft_putstr_fd("Change Fractal :\n", 1);
	ft_putstr_fd("Julia 1 = 'J'\n", 1);
	ft_putstr_fd("Julia 2 = 'K'\n", 1);
	ft_putstr_fd("Julia 3 = 'L'\n", 1);
	ft_putstr_fd("Mandelbrot = 'M'\n", 1);
	ft_putstr_fd("Burning Ship = 'B'\n\n", 1);
	ft_putstr_fd("Change colors :\n", 1);
	ft_putstr_fd("Numpad 0 to 2\n", 1);
}
////// TODO //////
/*
	-0- Welcome message with commands
	-1- Graphics Optimization
		https://mandelbrowser.y0.pl/tutorial/computing.html#coloring
		https://www.youtube.com/watch?v=EbanExb75mc]
		-1.1- Change Colors every n times

	-2- Differents Sets
		-2.3- Nova Fractals sets
			- https://rotgers.io/posts/nova-fractals/
		-2.4- Phoenix
			https://www.jamesh.id.au/fractals/mandel/phoenix
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
				show_commands();
				d->axis = axis;
				hook_init(d);
				put_pxl(d->image, &axis, d->axis->zoom);
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
