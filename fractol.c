/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesille <adesille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:52:57 by adesille          #+#    #+#             */
/*   Updated: 2023/12/07 17:58:09 by adesille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events-with-the-minilibx.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 19:56:59 by abrabant          #+#    #+#             */
/*   Updated: 2021/02/10 19:57:03 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include <mlx.h>
#include <X11/keysym.h>
#include <X11/X.h>

#define W_WIDTH 600
#define W_HEIGHT 300

#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}			t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int	height;
	int	color;
}		t_rect;

/* The x and y coordinates of the rect corresponds to its upper left corner */

int	render_rect(t_data *data, t_rect rect)
{
	int i;
	int j;

	if (data->win_ptr == NULL)
		return (1);
	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.color);
		++i;	
	}
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	printf("Keypress: %d\n", keysym);
	return(0);
}

int	render(t_data *data)
{
	render_rect(data, (t_rect){W_WIDTH - 100, W_HEIGHT - 100, 100, 100, GREEN_PIXEL});
	render_rect(data, (t_rect){0, 0, 100, 100, RED_PIXEL});
	return (0);
}

int	destroy_windows(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(1);
}

int main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "FUS RODAAAAA");
	if (!data.win_ptr)
		return(free(data.win_ptr), 1);
	
	/* Setup Hooks */
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0, destroy_windows, &data);

	mlx_loop(data.mlx_ptr); // loop that let the graphic server works

    /* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}

// lmlx -lXext -lX11