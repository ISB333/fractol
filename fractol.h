/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:33:26 by adesille          #+#    #+#             */
/*   Updated: 2024/04/23 16:19:43 by isb3             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "math.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <memory.h>
# define WIDTH 2000
# define HEIGHT 1000
# define R(a) (a) >> 16
# define G(a) ((a) >> 8) & 0xFF
# define B(a) (a) & 0xFF
# define RGB(a, b, c) ((a) << 16) + ((b) << 8) + (c)


typedef struct s_coord
{
	char	set;
	double	xr;
	double	yi;
	double	cr;
	double	ci;
	double	temp;
	int it;
}	t_coord;

typedef struct s_data
{
	mlx_image_t	*image;
	mlx_t		*mlx;
}	t_data;

int		complex_calc(char set, t_coord **axis);
int		put_pxl(uint32_t x, uint32_t y, mlx_image_t *image, t_coord **axis);
int		error(void);
int		ff(t_data *d, t_coord *axis);

#endif