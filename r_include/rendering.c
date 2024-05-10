/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:54:23 by isb3              #+#    #+#             */
/*   Updated: 2024/05/10 14:25:25 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

uint32_t	mono_shaders(double instability)
{
	int	startcolor = 0;
	int	endcolor = 0;

	startcolor = 0x04228eFF;
	endcolor = 0xbff9fcFF;
	return (((startcolor / endcolor) ^ (int)instability) * endcolor);
}

uint32_t	simple_shaders(double instability)
{
	int	startcolor = 0;
	int	endcolor = 0;

	// if ((int)instability % 4 == 0)
	// {
	// 	startcolor = 0xFF001EFF;
	// 	endcolor = 0xFF00A8FF;
	// }
	// else if ((int)instability % 4 == 1)
	// {
	// 	startcolor = 0xFF00A8FF;
	// 	endcolor = 0x1400FFFF;
	// }
	// else if ((int)instability % 4 == 2)
	// {
	// 	startcolor = 0x1400FFFF;
	// 	endcolor = 0x00F0FFFF;
	// }
	// else
	// {
	// 	startcolor = 0x00F0FFFF;
	// 	endcolor = 0x00FF1AFF;
	// }
	if ((int)instability % 4 == 0)
	{
		startcolor = 0x660050FF;
		endcolor = 0xFAFF00FF;
	}
	else if ((int)instability % 4 == 1)
	{
		startcolor = 0x100050FF;
		endcolor = 0xa7e500FF;
	}
	else if ((int)instability % 4 == 2)
	{
		startcolor = 0xFA0068FF;
		endcolor = 0xFFF700FF;
	}
	else
	{
		startcolor = 0x02008AFF;
		endcolor = 0x00FFFFFF;
	}
	return (((startcolor / endcolor) ^ (int)instability) * endcolor);
}

uint32_t	shaders_smooth(int startcolor, int endcolor, double instability)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

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

uint32_t	color_mode1(double instability)
{
	int	color1;
	int	color2;

	if ((int)instability % 4 == 0)
	{
		color1 = 0x660050FF;
		color2 = 0xFAFF00FF;
	}
	else if ((int)instability % 4 == 1)
	{
		color1 = 0x100050FF;
		color2 = 0xa7e500FF;
	}
	else if ((int)instability % 4 == 2)
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
	else if (axis->colormode == 'n')
		return (simple_shaders(instability));
	else if (axis->colormode == 'm')
		return (mono_shaders(instability));
	else if (axis->colormode == 'z')
		return (shaders_smooth(0xF400FFFF, 0xFF0000FF, instability));
	return (color_mode1(instability));
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
