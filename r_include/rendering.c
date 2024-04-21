/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:22:30 by adesille          #+#    #+#             */
/*   Updated: 2024/04/21 10:20:42 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// int32_t	pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
// 	return (r << 24 | g << 16 | b << 8 | a);
// }

double *convert_values(double x, double y)
{
	double	*ri;

	ri = NULL;
	ri = malloc (2 * sizeof(double));
	x -= (WIDTH / 2);
	y -= (HEIGHT / 2);
	ri[0] = x / 500;
	ri[1] = y / 500;
	return (ri);
}

uint32_t shaders(uint32_t color1, uint32_t color2, float percentage)
{
    uint8_t r1 = (color1 >> 16) & 0xFF;
    uint8_t g1 = (color1 >> 8) & 0xFF;
    uint8_t b1 = color1 & 0xFF;
    
    uint8_t r2 = (color2 >> 16) & 0xFF;
    uint8_t g2 = (color2 >> 8) & 0xFF;
    uint8_t b2 = color2 & 0xFF;
    
    uint8_t r = (uint8_t)(r1 + (r2 - r1) * percentage);
    uint8_t g = (uint8_t)(g1 + (g2 - g1) * percentage);
    uint8_t b = (uint8_t)(b1 + (b2 - b1) * percentage);
    
    return (uint32_t)((r << 16) | (g << 8) | b | 0xFF000000);
}

int put_pxl(uint32_t x, uint32_t y, mlx_image_t *image, t_coord **axis)
{
	uint32_t	shade;
	double		*ri;
	int			instability;

	y = 0;
	while (y < HEIGHT)
	{
		// -r, +i
		x = 0;
		while (x < WIDTH)
		{
			ri = convert_values((double)x, (double)y);
			instability = complex_calc('j', ri[0], ri[1]);
			if (!instability)
				mlx_put_pixel(image, x, y, 0x000000FF);
			else
			{
				shade = shaders(0xff0000FF, 0x3a2956FF, instability);
				mlx_put_pixel(image, x, y, shade);
			}
			x += 1;
		}
		y += 1;
	}
	return (0);
}
