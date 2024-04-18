/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 11:09:55 by adesille          #+#    #+#             */
/*   Updated: 2024/04/18 12:25:23 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	return (exit(EXIT_FAILURE), 1);
}

int32_t	pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	randomize(void *param)
{
	(void)param;
	uint32_t	i;
	uint32_t	y;
	uint32_t	color;

	i = -1;
	y = -1;
	while (++i < image->width)
		while (++y < image->height)
		{
			color = pixel(
				rand() % 0XFF, // R
				rand() % 0XFF, // G
				rand() % 0XFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
}

int32_t	main(void)
{
	mlx_t		*mlx;
	uint32_t	x;
	uint32_t	y;

	mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
	if (!mlx)
		error();
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image)
        return (mlx_close_window(mlx), error());
	if (mlx_image_to_window(mlx, image, 0, 0))
        return (mlx_close_window(mlx), error());

	// mlx_loop_hook(mlx, randomize, mlx);
	y = 50;
	while (y < 1000)
	{
		x = 50;
		while (x < 1000)
		{
			if (complex_calc(0, 0, x, y) == 1)
				mlx_put_pixel(image, x, y, 0x000000FF);
			else if (complex_calc(0, 0, x, y) == -1)
				mlx_put_pixel(image, x, y, 0xFFFFFFFF);
			// mlx_put_pixel(image, x, y, rand() % 0xffffff);
			x++;
		}
		y++;
	}

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
