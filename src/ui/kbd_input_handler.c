/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_input_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:49:56 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/09 10:17:55 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	handle_quit_destroy_keys(int key, t_mrt *mrt);
static void	handle_subsample(int key, t_mrt mrt);
static void	handle_fov(int key, t_mrt mrt);

int	kbd_input_handler(int key, t_mrt *mrt)
{
	printf("User pressed key: %d\n", key);
	handle_quit_destroy_keys(key, mrt);
	handle_subsample(key, *mrt);
	handle_fov(key, *mrt);
	return (0);
}

void	handle_subsample(int key, t_mrt mrt)
{
	if (key == 91)
	{
		mlx_clear_window(mrt.mlx, mrt.win);
		if (mrt.scene->subsample > 1)
			mrt.scene->subsample -= 1;
		show_sidebar(mrt);
		raytrace(mrt);
		draw_axis(mrt);
	}
	if (key == 93)
	{
		mlx_clear_window(mrt.mlx, mrt.win);
		if (mrt.scene->subsample < 100)
			mrt.scene->subsample++;
		show_sidebar(mrt);
		raytrace(mrt);
		draw_axis(mrt);
	}
}

void	handle_fov(int key, t_mrt mrt)
{
	t_camera	*cam;

	cam = mrt.scene->cam;
	if (key == 57)
	{
		if (cam->fov - 0.1 > 0)
		{
			cam->fov -= 0.1;
			cam->view_width = 2 * tan(cam->fov/2);
			cam->canvas_to_view_ratio = cam->view_width / CANVAS_WIDTH;
		}
		mlx_clear_window(mrt.mlx, mrt.win);
		show_sidebar(mrt);
		raytrace(mrt);
		draw_axis(mrt);
	}
	if (key == 48)
	{
		if (cam->fov + 0.1 < M_PI)
		{
			cam->fov += 0.1;
			cam->view_width = 2 * tan(cam->fov/2);
			cam->canvas_to_view_ratio = cam->view_width / CANVAS_WIDTH;
		}
		mlx_clear_window(mrt.mlx, mrt.win);
		show_sidebar(mrt);
		raytrace(mrt);
		draw_axis(mrt);
	}
}

void	handle_quit_destroy_keys(int key, t_mrt *mrt)
{
	if (key == 65307)
	{
		mlx_destroy_window(mrt->mlx, mrt->win);
		mlx_destroy_display(mrt->mlx);
		free(mrt->mlx);
		free(mrt);
		exit(0);
	}
}

