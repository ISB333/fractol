/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:54:23 by isb3              #+#    #+#             */
/*   Updated: 2024/05/08 14:26:35 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

uint32_t	shaders_smooth(int startcolor, int endcolor, double instability)
{
	double	increment[3];
	int		new[3];
	int		newcolor;
	
	// instability = log(instability) / log(4);
	increment[0] = (double)((R(endcolor)) - (R(startcolor)) / instability);
	increment[1] = (double)((G(endcolor)) - (G(startcolor)) / instability);
	increment[2] = (double)((B(endcolor)) - (B(startcolor)) / instability);
	new[0] = (R(startcolor)) + round(increment[0]);
	new[1] = (G(startcolor)) + round(increment[1]);
	new[2] = (R(startcolor)) + round(increment[2]);
	newcolor = RGB(new[0], new[1], new[2]);
	return (newcolor);
}
uint32_t	shaders1(int startcolor, int endcolor, double instability)
{
	double	increment[3];
	int		new[3];
	int		newcolor;
	
	// instability = log(instability) / log(4);
	increment[0] = (double)((R(endcolor)) - (R(startcolor)) / instability);
	increment[1] = (double)((G(endcolor)) - (G(startcolor)) / instability);
	increment[2] = (double)((B(endcolor)) - (B(startcolor)) / instability);
	new[0] = (R(startcolor)) + round(increment[0]);
	new[1] = (G(startcolor)) + round(increment[1]);
	new[2] = (R(startcolor)) + round(increment[2]);
	newcolor = RGB(new[0], new[1], new[2]);
	return (newcolor);
}

uint32_t	glitch_shaders(int startcolor, int endcolor, double len, int pix)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

	increment[0] = (double)((R(endcolor)) - (R(startcolor)) / len);
	increment[1] = (double)((G(endcolor)) - (G(startcolor)) / len);
	increment[2] = (double)((B(endcolor)) - (B(startcolor)) / len);
	new[0] = (R(startcolor)) + round(pix * increment[0]);
	new[1] = (G(startcolor)) + round(pix * increment[1]);
	new[2] = (B(startcolor)) + round(pix * increment[2]);
	newcolor = RGB(new[0], new[1], new[2]);
	return (newcolor);
}

uint32_t	shaders_mode1(double instability)
{
	int	color1;
	int	color2;

	if ((int)instability % 4 <= 1)
	{
		color1 = 0x660050FF;
		color2 = 0xFAFF00FF;
	}
	else if ((int)instability % 4 == 2)
	{
		color1 = 0x100050FF;
		color2 = 0xa7e500FF;
	}
	else if ((int)instability % 4 == 3)
	{
		color1 = 0xFA0068FF;
		color2 = 0xFFF700FF;
	}
	else
	{
		color1 = 0x02008AFF;
		color2 = 0x00FFFFFF;
	}
	return (shaders_smooth(color1, color2, instability));
}

uint32_t	shaders(double instability, double y, t_coord *axis)
{	

	if (axis->colormode == 'g')
		return (glitch_shaders(0xF400FFFF, 0xFF0000FF, instability, y));
	else
		return (shaders_mode1(instability));
	return (0);
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
			(*axis)->storage[y][x] = complex_calc((*axis)->set, axis);
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
