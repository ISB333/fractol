/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 11:09:55 by adesille          #+#    #+#             */
/*   Updated: 2024/04/18 16:16:26 by adesille         ###   ########.fr       */
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

// int put_pxl(uint32_t x, uint32_t y)
// {
	// uint32_t	r;
	// uint32_t	i;

	// y = HEIGHT;
	// while (y > HEIGHT / 2)
	// {
	// 	// -r, +i
	// 	x = 0;
	// 	while (x < WIDTH)
	// 	{
	// 		mlx_put_pixel(image, x, y, rand() % 0xffffff);
	// 		x++;
	// 	}
	// 	y--;
	// }
	// while (y > 0)
	// {
	// 	// -r, -i
	// 	x = 0;
	// 	while (x < WIDTH / 2)
	// 	{
	// 		mlx_put_pixel(image, x, y, 0xFFFFFFFF);
	// 		x++;
	// 	}
	// 	y--;
	// }
	// y = HEIGHT;
	// while (y > HEIGHT / 2)
	// {
	// 	// +r, +i
	// 	x = WIDTH / 2;
	// 	while (x < WIDTH)
	// 	{
	// 		mlx_put_pixel(image, x, y, 0x000000FF);
	// 		x++;
	// 	}
	// 	y--;
	// }
	// while (y > 0)
	// {
	// 	// +r, -i
	// 	x = WIDTH / 2;
	// 	while (x < WIDTH)
	// 	{
	// 		mlx_put_pixel(image, x, y, 0xFFF000FF);
	// 		x++;
	// 	}
	// 	y--;
	// }
// 	return (0);
// }

double *convert_values(double x, double y)
{
	double	*ri;

	ri = NULL;
	ri = malloc (2 * sizeof(double));
	x -= (WIDTH / 2);
	y -= (HEIGHT / 2);
	ri[0] = x / 1000;
	ri[1] = y / 1000;
	// printf("%f, %f", ri[0], ri[1]);
	return (ri);
}

int put_pxl(uint32_t x, uint32_t y)
{
	double *ri;

	y = 0;
	while (y < HEIGHT)
	{
		// -r, +i
		x = 0;
		while (x < WIDTH)
		{
			ri = convert_values((double)x, (double)y);
			if (complex_calc(0, 0, ri[0], ri[1]) == 1)
				mlx_put_pixel(image, x, y, 0x000000FF);
			else
				mlx_put_pixel(image, x, y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
	return (0);
}

int32_t	main(void)
{
	mlx_t		*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
	if (!mlx)
		error();
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image)
        return (mlx_close_window(mlx), error());
	if (mlx_image_to_window(mlx, image, 0, 0))
        return (mlx_close_window(mlx), error());

	put_pxl(0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
