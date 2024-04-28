/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:22:30 by adesille          #+#    #+#             */
/*   Updated: 2024/04/25 11:11:46by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// int32_t	pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
// 	return (r << 24 | g << 16 | b << 8 | a);
// }

void	convert_values(double x, double y, t_coord **axis, float zoom)
{
	x -= (WIDTH / 2);
	y -= (HEIGHT / 2);

	// Scale 
	if ((*axis)->x_zoom || (*axis)->y_zoom)
	{
		(*axis)->xr = x / 500 * zoom + (((*axis)->x_zoom - (WIDTH / 2)) / 500);
		(*axis)->yi = y / 500 * zoom + (((*axis)->y_zoom - (HEIGHT / 2)) / 500);
	}
	else
	{
		(*axis)->xr = x / 500;
		(*axis)->yi = y / 500;
	}
}

uint32_t shaders_to100(int startcolor, int endcolor, double len)
{
    double increment[3];
    int new[3];
    int newcolor;

	len *= 2.55;
    increment[0] = (double)((R(endcolor)) - (R(startcolor))) / len;
    increment[1] = (double)((G(endcolor)) - (G(startcolor))) / len;
    increment[2] = (double)((B(endcolor)) - (B(startcolor))) / len;

    // new[0] = (R(startcolor)) + round(pix * increment[0]);
    // new[1] = (G(startcolor)) + round(pix * increment[1]);
    // new[2] = (B(startcolor)) + round(pix * increment[2]);

    new[0] = (R(startcolor)) + round(increment[0]);
    new[1] = (G(startcolor)) + round(increment[1]);
    new[2] = (B(startcolor)) + round(increment[2]);

    newcolor = RGB(new[0], new[1], new[2]);

    return (newcolor);
}

uint32_t	shaders(float instability, uint32_t y)
{
	// if (instability <= 20)
	// 	return (shaders_to33(0x360000FF, 0x4CAF50FF, instability));
	// else if (instability <= 40)
	// else
	if (y > 1)
		return (shaders_to100(0xF400FFFF, 0xFF0000FF, instability));
	else
		return (shaders_to100(0x000000FF, 0xA100A1FF, instability));
}

int put_pxl(mlx_image_t *image, t_coord **axis, float zoom)
{
	uint32_t	shade;
	uint32_t	x;
	uint32_t	y;
	int			instability;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			convert_values((double)x, (double)y, axis, zoom);
			instability = complex_calc((*axis)->set, axis);
			if (!instability)
				mlx_put_pixel(image, x, y, 0x000000FF);
			else
			{
				if ((*axis)->it > 0)
					shade = shaders((double)instability, (*axis)->it);
				else
					shade = shaders((double)instability, (*axis)->it);
				mlx_put_pixel(image, x, y, shade);
			}
			x++;
		}
		y++;
	}
	return (0);
}
