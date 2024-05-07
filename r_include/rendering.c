/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:54:23 by isb3              #+#    #+#             */
/*   Updated: 2024/05/07 13:56:36 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

uint32_t	shaders1(int startcolor, int endcolor, double instability, t_coord *axis)
{
	double	increment[3];
	int		new[3];
	int		newcolor;
	
	increment[0] = (double)((R(endcolor)) - (R(startcolor)) / instability);
	increment[1] = (double)((G(endcolor)) - (G(startcolor)) / instability);
	increment[2] = (double)((B(endcolor)) - (B(startcolor)) / instability);
	new[0] = (R(startcolor)) + round(increment[0]);
	new[1] = (G(startcolor)) + round(increment[1]);
	new[0] = (R(startcolor)) + round(increment[0]);
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

uint32_t	shaders(double instability, double x, double y, t_coord *axis)
{
	int	color1;
	int	color2;

	if (!instability)
		return (glitch_shaders(0xF400FFFF, 0xFF0000FF, instability, y));
	else
	{
		// printf("%f\n", instability);
		// if (instability)
		// {
			color1 = 0xF400FFFF;
			color2 = 0xFF0000FF;
		// }
		// else if (instability <= 2)
		// {
			// color1 = 0x100050FF;
			// color2 = 0xa7e500FF;
		// }
		// else if (instability <= 3)
		// {
			// color1 = 0xFA0068FF;
		// 	color2 = 0xFFF700FF;
		// }
		// else
		// {
		// 	color1 = 0x02008AFF;
		// 	color2 = 0x00FFFFFF;
		// }
		return (shaders1(color1, color2, instability, axis));
	}
}

int	store_instability(t_coord **axis, float zoom)
{
	double	instability;
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			convert_to_axis((double)x, (double)y, axis, zoom);
			instability = complex_calc((*axis)->set, axis);
			(*axis)->storage[y][x] = instability;
			(*axis)->shade[y][x] = shaders(instability, (double)x, (double)y, *axis);
		}
		y++;
	}
	return (0);
}

int	put_pxl(mlx_image_t *image, t_coord **axis)
{
	uint32_t	shade;
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (!(*axis)->storage[y][x])
				mlx_put_pixel(image, x, y, 0x000000FF);
			else
				mlx_put_pixel(image, x, y, (*axis)->shade[y][x]);
		}
		y++;
	}
	return (0);
}
