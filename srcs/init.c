/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:38:15 by isb3              #+#    #+#             */
/*   Updated: 2024/05/21 14:09:29 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

int	julia_init_utils(t_coord **axis, char *argv[])
{
	long double	crtemp;
	long double	citemp;

	(*axis)->set = 'j';
	crtemp = ft_atod(argv[2]);
	citemp = ft_atod(argv[3]);
	if ((crtemp > DBL_MIN && crtemp < DBL_MAX) && \
		(citemp > DBL_MIN && citemp < DBL_MAX))
	{
		printf("%Lf\n%Lf\n", crtemp, citemp);
		(*axis)->cr = (double)crtemp;
		(*axis)->ci = (double)citemp;
		return (0);
	}
	printf("%Lf\n%Lf\n", crtemp, citemp);
	return (ft_putstr_fd("error: value overflow\n", 1), -1);
}

int	julia_init(t_coord **axis, char *argv[])
{
	(*axis)->set = 'j';
	if (argv[2] && argv[2][0] == '1' && !argv[2][1])
	{
		(*axis)->cr = 0.3;
		(*axis)->ci = 0.5;
	}
	else if (argv[2] && argv[2][0] == '2' && !argv[2][1])
	{
		(*axis)->cr = -1.476;
		(*axis)->ci = 0;
	}
	else if (argv[2] && argv[2][0] == '3' && !argv[2][1])
	{
		(*axis)->cr = 0.285;
		(*axis)->ci = 0.01;
	}
	else if (!is_nbr(argv[2]) && !is_nbr(argv[3]))
		return (julia_init_utils(axis, argv));
	else
		return (-1);
	return (0);
}

int	init_set(t_coord **axis, char *argv[])
{
	if ((!ft_strcmp("Mandelbrot", argv[1]) && !argv[2]) \
		|| (!ft_strcmp("mandelbrot", argv[1]) && !argv[2]))
		return ((*axis)->set = 'm', 0);
	else if (!ft_strcmp("Julia", argv[1]) || !ft_strcmp("julia", argv[1]))
		return (julia_init(axis, argv));
	else if ((!ft_strcmp("Burning", argv[1]) && !argv[2]) \
			|| (!ft_strcmp("burning", argv[1]) && !argv[2]))
	{
		(*axis)->cr = 0;
		(*axis)->ci = 0;
		return ((*axis)->set = 'b', 0);
	}
	return (-1);
}

t_coord	*parse_coord(t_coord **axis, char *argv[])
{
	*axis = malloc(sizeof(t_coord));
	if (*axis)
	{
		if (init_set(axis, argv))
			return (NULL);
		(*axis)->zoom = 1;
		(*axis)->colormode = 1;
	}
	return (*axis);
}
