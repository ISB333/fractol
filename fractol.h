/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:33:26 by adesille          #+#    #+#             */
/*   Updated: 2024/05/02 11:57:57 by isb3             ###   ########.fr       */
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
# define WIDTH 1200
# define HEIGHT 800
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
	int		it;
	double	zoom;
	uint32_t	x_shift;
	double	y_shift;
	int32_t	x_zoom;
	int32_t	y_zoom;
	uint32_t	storage[HEIGHT][WIDTH];
}	t_coord;

typedef struct s_data
{
	mlx_image_t	*image;
	mlx_image_t	*new_image;
	mlx_t		*mlx;
	t_coord		*axis;
}	t_data;

// typedef struct s_storage
// {
// }	t_storage;

t_data		*init_img(t_data **d);
t_coord		*parse_coord(t_coord **axis, char *argv[]);

int	stability_storage(t_coord **axis, float zoom);
int			put_pxl(mlx_image_t *image, t_coord **axis, float zoom);
uint32_t	complex_calc(char set, t_coord **axis);

void		convert_to_axis(double x, double y, t_coord **axis, float zoom);
int			error(void);
int			ff(t_data *d, t_coord *axis, int status);
void		command_set(char *msg);

#endif