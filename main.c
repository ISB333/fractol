/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 11:09:55 by adesille          #+#    #+#             */
/*   Updated: 2024/04/16 12:10:07 by adesille         ###   ########.fr       */
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

void	hook(void *param)
{
	mlx_t			*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 0;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

int32_t	main(void)
{
	mlx_t		*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "fractol", true);
	if (!mlx)
		error();
	image = mlx_new_image(mlx, 1280, 128);
	if (!image)
        return (mlx_close_window(mlx), error());
	if (mlx_image_to_window(mlx, image, 0, 0))
        return (mlx_close_window(mlx), error());
	mlx_loop_hook(mlx, randomize, mlx);
	mlx_loop_hook(mlx, hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
