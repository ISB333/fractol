/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:54:23 by isb3              #+#    #+#             */
/*   Updated: 2024/05/21 10:29:28 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*	sin(frequenc * continuous_index + phase) * center + delta)

	sin()) generate smooth oscillations values between -1 and 1.
	then they're scaled and shifted to fit within the range [0, 255]
*/
uint32_t	simple_shaders0(double inst)
{
	uint8_t			rgba[4];

	rgba[0] = (uint8_t)(sin(0.116 * inst + 4) * 127.5 + 127.25);
	rgba[1] = (uint8_t)(sin(0.0513 * inst + 2) * 127.5 + 127.5);
	rgba[2] = (uint8_t)(sin(0.01 * inst + 1) * 127.5 + 127.5);
	rgba[3] = 255;
	return (convert_rgba(rgba));
}

uint32_t	simple_shaders1(double inst)
{
	uint8_t		rgba[4];

	rgba[0] = (uint8_t)(sin(0.277490 * inst + 1) * 127.5 + 127.25);
	rgba[1] = (uint8_t)(sin(0.277490 * inst + 2) * 127.5 + 127.5);
	rgba[2] = (uint8_t)(sin(0.277490 * inst + 4) * 127.5 + 127.5);
	rgba[3] = 255;
	return (convert_rgba(rgba));
}

uint32_t	simple_shaders2(double instability)
{
	uint8_t		rgba[4];

	rgba[0] = (uint8_t)(sin(0.116 * instability + 1) * 127.5 + 127.25);
	rgba[1] = (uint8_t)(sin(0.513 * instability + 2) * 127.5 + 127.5);
	rgba[2] = (uint8_t)(sin(0.8 * instability + 4) * 127.5 + 127.5);
	rgba[3] = 255;
	return (convert_rgba(rgba));
}

//	R,G,B MACROS isolate th r,g,b values from the color given
uint32_t	shaders_smooth(int startcolor, int endcolor, \
							double instability, int pix)
{
	double	increment[3];
	int		new[3];
	int		rgb1[3];
	int		rgb2[3];

	rgb1[0] = (startcolor >> 16);
	rgb1[1] = (startcolor >> 8) & 0xFF;
	rgb1[2] = startcolor & 0xFF;
	rgb2[0] = (endcolor >> 16);
	rgb2[1] = (endcolor >> 8) & 0xFF;
	rgb2[2] = endcolor & 0xFF;
	increment[0] = (double)((rgb2[0] - rgb1[0]) / instability);
	increment[1] = (double)((rgb2[1] - rgb1[1]) / instability);
	increment[2] = (double)((rgb2[2] - rgb1[2]) / instability);
	new[0] = rgb1[0] + round(pix * increment[0]);
	new[1] = rgb1[1] + round(pix * increment[1]);
	new[2] = rgb1[2] + round(pix * increment[2]);
	return (convert_rgb(new));
}

uint32_t	smooth_mode1(double instability)
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
	return (shaders_smooth(color1, color2, instability, 1));
}
