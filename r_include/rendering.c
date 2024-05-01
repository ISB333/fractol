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
// Define the palette function to return a color as an array of float values
float* palette(float t, float a, float b, float c, float d)
{
    static float color[3];
    color[0] = a + b * cos(6.28318 * (c * t + d));
    color[1] = a + b * cos(6.28318 * (c * t + d + (2.0 / 3.0)));
    color[2] = a + b * cos(6.28318 * (c * t + d + (4.0 / 3.0)));
    return color;
}

// Modify the shaders function to return a uint32_t color value
uint32_t shaders2(double instability)
{
	float a1 = 0.618, b1 = 0.500, c1 = 0.500;
	float a2 = 0.078, b2 = 0.748, c2 = 0.500;
	float a3 = 1.000, b3 = 1.000, c3 = 1.000;
	float a4 = 0.000, b4 = 0.333, c4 = 0.667;

// Assuming d is not provided in the input vectors, set d to 0.0 for all vectors
	float d1 = 0.0, d2 = 0.0, d3 = 0.0, d4 = 0.0;

	float* color1 = palette(instability, a1, b1, c1, d1);
	float* color2 = palette(instability, a2, b2, c2, d2);
	float* color3 = palette(instability, a3, b3, c3, d3);
	// float* color4 = palette(t, a4, b4, c4, d4);

    int r = (int)(255.0 * color1[1]);
    int g = (int)(255.0 * color1[2]);
    int b = (int)(255.0 * color1[3]);
    uint32_t newcolor = RGB(r, g, b);
    return newcolor;
}


uint32_t glitch_shaders(int startcolor, int endcolor, double len, int pix)
{
    double increment[3];
    int new[3];
    int newcolor;

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

uint32_t shaders1(int startcolor, int endcolor, int len, int pix)
{
    double increment[3];
    int new[3];
    int newcolor;

	len = sin(len);
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

uint32_t	shaders(double instability, double x, double y)
{
	// x /= 100;
	// y /= 100;

	if (instability)
		return (glitch_shaders(0xF400FFFF, 0xFF0000FF, instability, y));
		// return (shaders1(0xF400FFFF, 0xFF0000FF, instability, y));
	else
		return (shaders2(y));
		// return (glitch_shaders(0xF400FFFF, 0xFF0000FF, instability, y));
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
				shade = shaders((double)instability, (double)x, (double)y);
				mlx_put_pixel(image, x, y, shade);
			}
			x++;
		}
		y++;
	}
	return (0);
}
