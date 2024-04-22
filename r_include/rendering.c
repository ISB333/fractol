/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:22:30 by adesille          #+#    #+#             */
/*   Updated: 2024/04/22 11:56:17 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// int32_t	pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
// 	return (r << 24 | g << 16 | b << 8 | a);
// }

void	convert_values(double x, double y, t_coord **axis)
{
	x -= (WIDTH / 2);
	y -= (HEIGHT / 2);
	(*axis)->xr = x / 500;
	(*axis)->yi = y / 500;
}

// uint32_t shaders(int startcolor, int endcolor, int len, int pix)
// {
//     double increment[3];
//     int new[3];
//     int newcolor;

//     increment[0] = (double)((R(endcolor)) - (R(startcolor))) / (double)len;
//     increment[1] = (double)((G(endcolor)) - (G(startcolor))) / (double)len;
//     increment[2] = (double)((B(endcolor)) - (B(startcolor))) / (double)len;

//     new[0] = (R(startcolor)) + round(pix * increment[0]);
//     new[1] = (G(startcolor)) + round(pix * increment[1]);
//     new[2] = (B(startcolor)) + round(pix * increment[2]);

//     newcolor = RGB(new[0], new[1], new[2]);

//     return (newcolor);
// }

// int32_t mlx_get_pixel(mlx_image_t* image, uint32_t x, uint32_t y)
// {
//   if (x > image->width || y > image->height)
//     return 0xFF000000;
//   uint8_t* pixelstart = image->pixels + (y * image->width + x) * BPP;
//   image->
//   return get_rgba(*(pixelstart), *(pixelstart + 1),
//     * (pixelstart + 2), *(pixelstart + 3));
// }

//==========================================================================
// uint32_t shaders(uint32_t color1, uint32_t color2, float percentage)
// {
//     uint8_t r1 = (color1 >> 16);
//     uint8_t g1 = (color1 >> 8) & 0xFF;
//     uint8_t b1 = color1 & 0xFF;
    
//     uint8_t r2 = (color2 >> 16);
//     uint8_t g2 = (color2 >> 8) & 0xFF;
//     uint8_t b2 = color2 & 0xFF;

//     uint8_t r = (uint8_t)(r1 + (r2 - r1) * percentage);
//     uint8_t g = (uint8_t)(g1 + (g2 - g1) * percentage);
//     uint8_t b = (uint8_t)(b1 + (b2 - b1) * percentage);

//     return (uint32_t)((r << 16) | (g << 8) | b | 0xFF000000);
// }
//==========================================================================

uint32_t shaders_to100(uint32_t color1, uint32_t color2, float percentage)
{
    uint8_t r1 = (color1 >> 16);
    uint8_t g1 = (color1 >> 8) & 0xFF;
    uint8_t b1 = color1 & 0xFF;
    
    uint8_t r2 = (color2 >> 16);
    uint8_t g2 = (color2 >> 8) & 0xFF;
    uint8_t b2 = color2 & 0xFF;

    uint8_t r = (uint8_t)(r1 + (r2 - r1) * percentage);
    uint8_t g = (uint8_t)(g1 + (g2 - g1) * percentage);
    uint8_t b = (uint8_t)(b1 + (b2 - b1) * percentage);

    return (uint32_t)((r << 16) | (g << 8) | b | 0xFF000000);
}

uint32_t shaders_to66(uint32_t color1, uint32_t color2, float percentage)
{
    uint8_t r1 = (color1 >> 16);
    uint8_t g1 = (color1 >> 8) & 0xFF;
    uint8_t b1 = color1 & 0xFF;
    
    uint8_t r2 = (color2 >> 16);
    uint8_t g2 = (color2 >> 8) & 0xFF;
    uint8_t b2 = color2 & 0xFF;

    uint8_t r = (uint8_t)(r1 + (r2 - r1) * percentage);
    uint8_t g = (uint8_t)(g1 + (g2 - g1) * percentage);
    uint8_t b = (uint8_t)(b1 + (b2 - b1) * percentage);

    return (uint32_t)((r << 16) | (g << 8) | b | 0xFF000000);
}

uint32_t shaders_to33(uint32_t color1, uint32_t color2, float percentage)
{
    uint8_t r1 = (color1 >> 16);
    uint8_t g1 = (color1 >> 8) & 0xFF;
    uint8_t b1 = color1 & 0xFF;
    
    uint8_t r2 = (color2 >> 16);
    uint8_t g2 = (color2 >> 8) & 0xFF;
    uint8_t b2 = color2 & 0xFF;

    uint8_t r = (uint8_t)(r1 + (r2 - r1) * percentage);
    uint8_t g = (uint8_t)(g1 + (g2 - g1) * percentage);
    uint8_t b = (uint8_t)(b1 + (b2 - b1) * percentage);

    return (uint32_t)((r << 16) | (g << 8) | b | 0xFF000000);
}

uint32_t	shaders(float instability)
{
	if (instability <= 33)
		return (shaders_to33(0x360000FF, 0x4CAF50FF, instability));
	else if (instability <= 66)
		return (shaders_to66(0xF400FFFF, 0xFF0000FF, instability));
	else
		return (shaders_to100(0xE52B2BFF, 0x1F11CEFF, instability));
}

int put_pxl(uint32_t x, uint32_t y, mlx_image_t *image, t_coord **axis)
{
	uint32_t	shade;
	// double		*ri;
	int			instability;

	while (y < HEIGHT)
	{
		// -r, +i
		x = 0;
		while (x < WIDTH)
		{
			convert_values((double)x, (double)y, axis);
			instability = complex_calc((*axis)->set, axis);
			if (!instability)
				mlx_put_pixel(image, x, y, 0x000000FF);
			else
			{
				printf("%d\n", instability);
				//lol
				// shade = shaders(0x360000FF, 0x4CAF50FF, instability, y);
				shade = shaders(instability);
				mlx_put_pixel(image, x, y, shade);
			}
			// printf("%d\n\n", image->pixels);
			x += 1;
		}
		y++;
	}
	return (0);
}
