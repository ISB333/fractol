/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:38:15 by isb3              #+#    #+#             */
/*   Updated: 2024/05/04 11:28:10 by isb3             ###   ########.fr       */
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
void	reinit_shift(t_data **d)
{
	d->axis->right_shift = 0;
	d->axis->left_shift = 0;
	d->axis->up_shift = 0;
	d->axis->down_shift = 0;
}

t_coord	*parse_coord(t_coord **axis, char *argv[])
{
	*axis = malloc(sizeof(t_coord));
	if (*axis)
	{
		if (!ft_strcmp("Mandelbrot", argv[1]) \
			|| !ft_strcmp("mandelbrot", argv[1]))
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
			else
				return (NULL);
		}
		else if (!ft_strcmp("Burning Ship", argv[1]) \
				|| !ft_strcmp("burning", argv[1]))
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
	(*axis)->zoom = 1;
	(*axis)->x_zoom = 0;
	(*axis)->y_zoom = 0;
	(*axis)->right_shift = 0;
	(*axis)->left_shift = 0;
	(*axis)->up_shift = 0;
	(*axis)->down_shift = 0;
	return (*axis);
}
