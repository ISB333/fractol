/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:54:23 by isb3              #+#    #+#             */
/*   Updated: 2024/05/02 11:33:41 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

uint32_t	shaders1(int startcolor, int endcolor, double instability, t_coord *axis)
{
	double	increment[3];
	double	smooth;
	int		new[3];
	int		newcolor;
	
	smooth = (float)instability - log2(log(pow(axis->cr, 2) + pow(axis->ci, 2)) / log(2));
	increment[0] = (double)((R(endcolor)) - (R(startcolor)) / smooth);
	increment[1] = (double)((G(endcolor)) - (G(startcolor)) / smooth);
	increment[2] = (double)((B(endcolor)) - (B(startcolor)) / smooth);
	new[0] = (R(startcolor)) + round(increment[0]);
	new[1] = (G(startcolor)) + round(increment[1]);
	new[2] = (B(startcolor)) + round(increment[2]);
	newcolor = RGB(new[0], new[1], new[2]);
	return (newcolor);
}

uint32_t	glitch_shaders(int startcolor, int endcolor, double len, int pix)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

	len = sin(len);
	pix -= HEIGHT / 2;
	increment[0] = (double)((R(endcolor)) - (R(startcolor)) / len);
	increment[1] = (double)((G(endcolor)) - (G(startcolor)) / len);
	increment[2] = (double)((B(endcolor)) - (B(startcolor)) / len);
	new[0] = (R(startcolor)) + round(pix * increment[0]);
	new[1] = (G(startcolor)) + round(pix * increment[1]);
	new[2] = (B(startcolor)) + round(pix * increment[2]);
	newcolor = RGB(new[0], new[1], new[2]);
	return (newcolor);
}

uint32_t	shaders(double instability, double x, double y, t_coord *axis)
{
	if (instability)
		return (glitch_shaders(0xF400FFFF, 0xFF0000FF, instability, y));
		// return (shaders1(0xF400FFFF, 0xFF0000FF, instability, y));
	else
		return (shaders1(0xF400FFFF, 0xFF0000FF, instability, axis));
		// return (glitch_shaders(0xF400FFFF, 0xFF0000FF, instability, y));
}

int	stability_storage(mlx_image_t *image, t_coord **axis, float zoom)
{
	uint32_t	instability;
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			convert_to_axis((double)x, (double)y, axis, zoom);
			instability = complex_calc((*axis)->set, axis);
			(*axis)->storage[y][x++] = instability;
		}
		y++;
	}
}
int	put_pxl(mlx_image_t *image, t_coord **axis, float zoom)
{
	uint32_t	shade;
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (!(*axis)->storage[y][x])
				mlx_put_pixel(image, x, y, 0x000000FF);
			else
			{
				shade = shaders((double)(*axis)->storage[y][x], (double)x, (double)y, *axis);
				mlx_put_pixel(image, x, y, shade);
			}
			x++;
			// storage(x, y, instability, axis);
		}
		y++;
	}
	return (0);
}
