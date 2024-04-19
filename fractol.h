/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:33:26 by adesille          #+#    #+#             */
/*   Updated: 2024/04/19 15:52:46 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <memory.h>
# define WIDTH 2000
# define HEIGHT 2000

typedef struct data
{
	// uint32_t
	mlx_image_t	*image;
	mlx_t		*mlx;

}	t_data;

int		complex_calc(double r, double i, double cr, double ci);
int		error(void);
int		put_pxl(uint32_t x, uint32_t y, mlx_image_t *image);

#endif