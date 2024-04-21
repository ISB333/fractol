/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:33:26 by adesille          #+#    #+#             */
/*   Updated: 2024/04/21 10:51:01 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <memory.h>
# define WIDTH 1000
# define HEIGHT 1000

typedef struct s_coord
{
	char	set;
	double	zr;
	double	zi;
	double	cr;
	double	ci;
	double	temp;
}	t_coord;

typedef struct s_data
{
	mlx_image_t	*image;
	mlx_t		*mlx;
}	t_data;

int		complex_calc(char set, double x, double y);
int		error(void);
int		put_pxl(uint32_t x, uint32_t y, mlx_image_t *image, t_coord **axis);

#endif