/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:36:34 by adesille          #+#    #+#             */
/*   Updated: 2024/04/22 16:48:49 by isb3             ###   ########.fr       */
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

t_coord	*parse_coord(t_coord **axis, char *s_set)
{
	*axis = malloc(sizeof(t_coord));
	if (*axis)
	{
		if (!ft_strcmp("Julia", s_set) || !ft_strcmp("julia", s_set))	
		{
			(*axis)->set = 'j';
			(*axis)->cr = 0.3;
			(*axis)->ci = 0.5;
		}
		else if (!ft_strcmp("Mandelbrot", s_set) || !ft_strcmp("mandelbrot", s_set))
			(*axis)->set = 'm';
		else if (!ft_strcmp("Templar", s_set) || !ft_strcmp("templar", s_set))
		{
			(*axis)->set = 'j';
			(*axis)->cr = -1.476;
			(*axis)->ci = 0;
		}
		else if (!ft_strcmp("Burning Ship", s_set) || !ft_strcmp("burning", s_set))
		{
			(*axis)->set = 'b';
			(*axis)->cr = -1.476;
			(*axis)->ci = 0;
		}
		else if (!ft_strcmp("Nova", s_set) || !ft_strcmp("nova", s_set))
		{
			(*axis)->set = 'n';
			(*axis)->cr = 0;
			(*axis)->ci = 0;
		}
	}
	return (*axis);
}
/////// TO MOTHERFUCKING DO /////
/*
	-0- f(z) = sin(z) +c
		- https://rotgers.io/posts/sinz_fractal/
		- https://dev.to/freerangepixels/a-probably-terrible-way-to-render-gradients-1p3n
	-1- Zoom & Dezoom (following mouse)
	-2- Window Management
		-2.1- ESC == Quit
		-2.2- Increase Window H/W by Window Size (mlx_resizefunc)

	-3- Differents Sets
		-3.1- Julia Sets (Presets + argv given)
		-3.2- Nova Fractals sets
			- https://rotgers.io/posts/nova-fractals/
	-4- Parameters by arg given
		-4.1- If no or wrong parameters == quit and Show params available
	-5- Move View through Arrow Keys
	-6- Color Shift
*/

int32_t	main(void)
{
	t_data	*d;
	t_coord	*axis;

	d = NULL;
	axis = NULL;
	if (init_img(&d) && parse_coord(&axis, "Mandelbrot"))
	{
		put_pxl(0, 0, d->image, &axis);
		// create_window()
		if (mlx_image_to_window(d->mlx, d->image, 0, 0))
			return (mlx_close_window(d->mlx), error());		
		mlx_loop(d->mlx);
		if (mlx_scroll_func())
		mlx_terminate(d->mlx);
		return (ff(d, axis), printf("Success!\n"), EXIT_SUCCESS);
	}
	mlx_terminate(d->mlx);
	return (ff(d, axis), printf("error\n"), 1);
}
