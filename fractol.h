/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:33:26 by adesille          #+#    #+#             */
/*   Updated: 2024/05/22 10:18:11 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <memory.h>
# include <float.h>
# include <limits.h>
# define WIDTH 800
# define HEIGHT 800
# define ESCAPE 50

typedef struct s_coord
{
	char		colormode;
	char		set;
	double		xr;
	double		yi;
	double		cr;
	double		ci;
	double		zoom;
	double		x_shift;
	double		y_shift;
	int32_t		x_zoom;
	int32_t		y_zoom;
	double		storage[HEIGHT][WIDTH];
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
int			init_set(t_coord **axis, char *argv[]);
int			is_nbr(char *str);
long double	ft_atod(char *nptr, int i);
void		hook_init(t_data *d);

int			put_pxl(mlx_image_t *image, t_coord **axis, double zoom);
int			shift_put_pxl(mlx_image_t *image, t_coord **axis);
double		complex_calcul(char set, t_coord **axis);
void		ft_abs(t_coord **axis);

uint32_t	simple_shaders0(double instability);
uint32_t	simple_shaders1(double instability);
uint32_t	simple_shaders2(double instability);
uint32_t	shaders_smooth(int startcolor, int endcolor, \
			double instability, int pix);
uint32_t	smooth_mode1(double instability);

void		rlshift_storage(t_data *d, char key);
void		dushift_storage(t_data *d, char key);

void		convert_to_axis(double x, double y, t_coord **axis, double zoom);
int			error(void);
int			ff(t_data *d, t_coord *axis, int status);
void		command_set(char *msg);
uint32_t	convert_rgba(uint8_t values[4]);
int			convert_rgb(int values[3]);

#endif