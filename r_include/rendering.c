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

/*


*/

uint32_t glitch_shaders(int startcolor, int endcolor, double len, int pix)
{
    double increment[3];
    int new[3];
    int newcolor;

    increment[0] = (double)((R(endcolor)) - (R(startcolor)) / len);
    increment[1] = (double)((G(endcolor)) - (G(startcolor)) / len);
    increment[2] = (double)((B(endcolor)) - (B(startcolor)) / len);

    new[0] = (R(startcolor)) + round(pix * increment[0]);
    new[1] = (G(startcolor)) + round(pix * increment[1]);
    new[2] = (B(startcolor)) + round(pix * increment[2]);

    newcolor = RGB(new[0], new[1], new[2]);

    return (newcolor);
}

uint32_t shaders1(int startcolor, int endcolor, double len, int pix)
{
    double increment[3];
    int new[3];
    int newcolor;

	len *= 1.55;
    increment[0] = (double)(218 - 204);
	// printf("R = %f\n", increment[0]);
    increment[1] = (double)((222 - 5));
	// printf("G = %f\n", increment[1]);
    increment[2] = (double)(23 - 5);
	// printf("B = %f\n", increment[2]);

    new[0] = (204 + round(len * increment[0]));
    new[1] = (5 + round(len * increment[1]));
    new[2] = (5 + round(len * increment[2]));
	// printf("%d, %d, %d\n", new[0], new[1], new[2]);

    newcolor = RGB(new[0], new[1], new[2]);

    return (newcolor);
}

uint32_t	shaders(float instability, uint32_t y)
{
	if (instability)
		return (shaders1(0xF400FFFF, 0xFF0000FF, instability, y));
	else
		return (glitch_shaders(0xF400FFFF, 0xFF0000FF, instability, y));
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
			convert_to_axis((double)x, (double)y, axis, zoom);
			instability = complex_calc((*axis)->set, axis);
			if (!instability)
				mlx_put_pixel(image, x, y, 0x000000FF);
			else
			{
				shade = shaders((double)instability, y);
				mlx_put_pixel(image, x, y, shade);
			}
			x++;
		}
		y++;
	}
	return (0);
}
