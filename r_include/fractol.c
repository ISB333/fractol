/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:36:34 by adesille          #+#    #+#             */
/*   Updated: 2024/04/24 12:28:54 by adesille         ###   ########.fr       */
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

t_data	*init_img(t_data **d)
{
	*d = malloc(sizeof(t_data));
	if (*d)
	{
		(*d)->mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
		if (!(*d)->mlx)
			return (error(), NULL);
		(*d)->image = mlx_new_image((*d)->mlx, WIDTH, HEIGHT);
		if (!(*d)->image)
			return (mlx_close_window((*d)->mlx), error(), NULL);
	}
	return (*d);
}

t_coord	*parse_coord(t_coord **axis, char *argv[])
{
	*axis = malloc(sizeof(t_coord));
	if (*axis)
	{
		if (!ft_strcmp("Mandelbrot", argv[1]) || !ft_strcmp("mandelbrot", argv[1]))
			(*axis)->set = 'm';
		else if (!ft_strcmp("Julia", argv[1]) || !ft_strcmp("julia", argv[1]))	
		{
			if (argv[2] && argv[2][0] == '1' && !argv[2][1])
			{
				(*axis)->set = 'j';
				(*axis)->cr = 0.3;
				(*axis)->ci = 0.5;
			}
			else if (argv[2] && argv[2][0] == '2' && !argv[2][1])
			{
				(*axis)->set = 'j';
				(*axis)->cr = -1.476;
				(*axis)->ci = 0;
			}
		}
		else if (!ft_strcmp("Burning Ship", argv[1]) || !ft_strcmp("burning", argv[1]))
		{
			(*axis)->set = 'b';
			(*axis)->cr = -1.476;
			(*axis)->ci = 0;
		}
		else if (!ft_strcmp("Nova", argv[1]) || !ft_strcmp("nova", argv[1]))
		{
			(*axis)->set = 'n';
			(*axis)->cr = 0;
			(*axis)->ci = 0;
		}
		else
			return (NULL);
	}
	return (*axis);
}
/////// TO MOTHERFUCKING DO /////
/*
	-1- Zoom & Dezoom (following mouse)
		- Scroll 5%
		- Get x, y => new 0
	-2- Window Management
		-2.1- ESC == Quit
		-2.2- Increase Window H/W by Window Size (mlx_resizefunc)
	-3- Differents Sets
		-3.1- Julia Sets (Presets + argv given)
		-3.2- Nova Fractals sets
			- https://rotgers.io/posts/nova-fractals/
=================================================================
	-4- f(z) = sin(z) +c
		- https://rotgers.io/posts/sinz_fractal/
		- https://dev.to/freerangepixels/a-probably-terrible-way-to-render-gradients-1p3n
	-5- Parameters by arg given
		-4.1- If no or wrong parameters == quit and Show params available
	-6- Move View through Arrow Keys
	-7- Color Shift
*/

void	command_set(char *msg)
{
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("Choose one the following possibilities :\n\n", 1);
	ft_putstr_fd(" -1-  Mandelbrot\n", 1);
	ft_putstr_fd("-2.1- Julia Preset 1 (Type Julia 1)\n", 1);
	ft_putstr_fd("-2.2- Julia Preset 2 (Type Julia 2)\n", 1);
	ft_putstr_fd("-2.3- Julia Preset 3 (Type Julia 3)\n", 1);
	ft_putstr_fd("-2.3- Julia Preset of your choices (Type Julia *complex number*)\n\n", 1);
}

void	mlx_scroller(void *param)
{
	t_data *d = param;
	
	d->new_image = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->new_image)
		return ;
		// return (mlx_close_window(d->mlx), error(), NULL);
	put_pxl(0, 500, d->new_image, d->axis);
}


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
			axis->it = 0;
			if (init_img(&d))
			{
				put_pxl(0, 0, d->image, &axis);
				if (mlx_image_to_window(d->mlx, d->image, 0, 0) == -1)
					return (mlx_close_window(d->mlx), error());		
				d->axis = &axis;
				mlx_scroll_hook(d->mlx, mlx_scroller, d);
				mlx_loop(d->mlx);
				mlx_close_window(d->mlx);
				mlx_delete_image(d->mlx, d->image);
			}
		}
		return (ff(d, axis), command_set("Invalid arguments !\n"), 1);
	}
	return (command_set("No arguments given !\n"), 0);
}
