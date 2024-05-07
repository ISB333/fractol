/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:33:26 by adesille          #+#    #+#             */
/*   Updated: 2024/05/07 13:53:25 by adesille         ###   ########.fr       */
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
# include <float.h>
# define WIDTH 1200
# define HEIGHT 800
# define R(a) (a) >> 16
# define G(a) ((a) >> 8) & 0xFF
# define B(a) (a) & 0xFF
# define RGB(a, b, c) ((a) << 16) + ((b) << 8) + (c)

typedef struct s_coord
{
	char		set;
	double		xr;
	double		yi;
	double		cr;
	double		ci;
	double		temp;
	int			color;
	// int			instability;
	// double		smooth_inst;
	double		zoom;
	double		x_shift;
	double		y_shift;
	int32_t		x_zoom;
	int32_t		y_zoom;
	double		storage[HEIGHT][WIDTH];
	uint32_t		shade[HEIGHT][WIDTH];
}	t_coord;

typedef struct s_data
{
	mlx_image_t	*image;
	mlx_image_t	*new_image;
	mlx_t		*mlx;
	t_coord		*axis;
}	t_data;

t_data		*init_img(t_data **d);
t_coord		*parse_coord(t_coord **axis, char *argv[]);
int			is_nbr(char *str);
long double		ft_atod(char *nptr);

int			store_instability(t_coord **axis, float zoom);
int			recalc_instability(t_coord **axis, float zoom);
int			put_pxl(mlx_image_t *image, t_coord **axis);
double		complex_calc(char set, t_coord **axis);
uint32_t	shaders(double instability, double x, double y, t_coord *axis);


void		rlshift_storage(t_data *d, char key);
void		dushift_storage(t_data *d, char key);

void		convert_to_axis(double x, double y, t_coord **axis, float zoom);
int			error(void);
int			ff(t_data *d, t_coord *axis, int status);
void		command_set(char *msg);

#endif