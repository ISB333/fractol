/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_shift.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:19:03 by isb3              #+#    #+#             */
/*   Updated: 2024/05/04 13:21:22 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	uconvert_to_axis(double x, double y, t_coord **axis, float zoom)
{
	x -= (WIDTH / 2);
	y -= (HEIGHT / 2);
	y *= -1;
	if ((*axis)->x_zoom || (*axis)->y_zoom)
	{
		(*axis)->xr += ((*axis)->x_zoom - WIDTH / 2) / 300;
		(*axis)->yi += ((*axis)->y_zoom - HEIGHT / 2) / 300;
		(*axis)->yi *= -1;
	}
	y -= (*axis)->up_shift - (*axis)->down_shift;
	(*axis)->xr = ((x / 300) * zoom);
	(*axis)->yi = ((y / 300) * zoom);
}

int	ustore_instability(t_coord **axis, float zoom)
{
	double	instability;
	uint32_t	x;
	uint32_t	y;

	y = HEIGHT - 90;
	while (y < HEIGHT)
	{
		x = - 1;
		while (++x < WIDTH)
		{
			uconvert_to_axis((double)x, (double)y, axis, zoom);
			instability = complex_calc((*axis)->set, axis);
			(*axis)->storage[y][x] = instability;
		}
		y++;
	}
	return (0);
}

void	ushift_storage(t_data *d)
{
	uint32_t	x;
	uint16_t	y;

	y = 0;
	while (y < HEIGHT - 90)
	{
		x = -1;
		while (++x < WIDTH)
			d->axis->storage[y][x] = d->axis->storage[y + 90][x];
		y++;
	}
	ustore_instability(&d->axis, d->axis->zoom);
	put_pxl(d->image, &d->axis);
}
