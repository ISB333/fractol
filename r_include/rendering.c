/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:54:23 by isb3              #+#    #+#             */
/*   Updated: 2024/05/10 14:42:01 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

uint32_t	shaders(double instability, double y, t_coord *axis)
{	
	if (axis->colormode == 'g')
		return (glitch_shaders(0xF400FFFF, 0xFF0000FF, instability, y));
	else if (axis->colormode == 'n')
		return (simple_shaders(instability));
	else if (axis->colormode == 'm')
		return (mono_shaders(instability));
	else if (axis->colormode == 'z')
		return (shaders_smooth(0xF400FFFF, 0xFF0000FF, instability));
	return (smooth_mode1(instability));
}

int	shift_put_pxl(mlx_image_t *image, t_coord **axis)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	shade;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (!(*axis)->storage[y][x])
				mlx_put_pixel(image, x, y, 0x000000FF);
			else
			{
				shade = shaders((*axis)->storage[y][x], (double)y, *axis);
				mlx_put_pixel(image, x, y, shade);
			}
		}
	}
	return (0);
}

int	put_pxl(mlx_image_t *image, t_coord **axis, double zoom)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	shade;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			convert_to_axis((double)x, (double)y, axis, zoom);
			(*axis)->storage[y][x] = complex_calcul((*axis)->set, axis);
			if (!(*axis)->storage[y][x])
				mlx_put_pixel(image, x, y, 0x000000FF);
			else
			{
				shade = shaders((*axis)->storage[y][x], (double)y, *axis);
				mlx_put_pixel(image, x, y, shade);
			}
		}
	}
	return (0);
}
