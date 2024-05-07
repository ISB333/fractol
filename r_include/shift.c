/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:19:03 by isb3              #+#    #+#             */
/*   Updated: 2024/05/07 09:59:07 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	update_xy_shift(t_coord **axis, char key)
{
	if (key == 'r')
		(*axis)->x_shift -= 0.3 * (*axis)->zoom;
	else if (key == 'l')
		(*axis)->x_shift += 0.3 * (*axis)->zoom;
	else if (key == 'd')
		(*axis)->y_shift -= 0.3 * (*axis)->zoom;
	else if (key == 'u')
		(*axis)->y_shift += 0.3 * (*axis)->zoom;
}

void	rlstore_instability(t_coord **axis, float zoom, char key)
{
	double		instability;
	uint32_t	x;
	uint32_t	y;
	uint32_t	w;

	y = -1;
	if (key == 'r')
		w = 90;
	else
		w = WIDTH;
	while (++y < HEIGHT)
	{
		if (key == 'r')
			x = -1;
		else
			x = WIDTH - 90 - 1;
		while (++x <= w)
		{
			convert_to_axis((double)x, (double)y, axis, zoom);
			instability = complex_calc((*axis)->set, axis);
			(*axis)->storage[y][x] = instability;
			(*axis)->shade[y][x] =  shaders(instability, (double)x, (double)y, *axis);
		}
	}
}

void	rlshift_storage(t_data *d, char key)
{
	uint32_t	x;
	uint16_t	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (key == 'r')
		{
			x = WIDTH;
			while (--x > 90)
			{
				d->axis->storage[y][x] = d->axis->storage[y][x - 90];
				d->axis->shade[y][x] = d->axis->shade[y][x - 90];
			}
		}
		else
		{
			x = -1;
			while (++x < WIDTH - 90)
			{
				d->axis->storage[y][x] = d->axis->storage[y][x + 90];
				d->axis->shade[y][x] = d->axis->shade[y][x + 90];
			}
		}
		y++;
	}
	update_xy_shift(&d->axis, key);
	rlstore_instability(&d->axis, d->axis->zoom, key);
}

void	dustore_instability(t_coord **axis, float zoom, char key)
{
	double		instability;
	uint32_t	x;
	uint32_t	y;
	uint32_t	h;

	if (key == 'd')
	{
		y = -1;
		h = 91;
	}
	else
	{
		y = HEIGHT - 91;
		h = HEIGHT;
	}
	while (++y < h)
	{
		x = -1;
		while (++x < WIDTH)
		{
			convert_to_axis((double)x, (double)y, axis, zoom);
			instability = complex_calc((*axis)->set, axis);
			(*axis)->storage[y][x] = instability;
			(*axis)->shade[y][x] =  shaders(instability, (double)x, (double)y, *axis);
		}
	}
}

void	dushift_storage(t_data *d, char key)
{
	uint32_t	x;
	uint32_t	y;

	if (key == 'd')
	{
		y = HEIGHT;
		while (--y > 90)
		{
			x = -1;
			while (++x < WIDTH)
			{
				d->axis->storage[y][x] = d->axis->storage[y - 90][x];
				d->axis->shade[y][x] = d->axis->shade[y - 90][x];
			}
		}
	}
	else
	{
		y = -1;
		while (++y < HEIGHT - 90)
		{
			x = -1;
			while (++x < WIDTH)
			{
				d->axis->storage[y][x] = d->axis->storage[y + 90][x];
				d->axis->shade[y][x] = d->axis->shade[y + 90][x];
			}
		}
	}
	update_xy_shift(&d->axis, key);
	dustore_instability(&d->axis, d->axis->zoom, key);
}
