/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_stuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:29:11 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/08 14:48:16 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void draw_axis(t_mrt mrt)
{
	int i;
	t_colr	c = {42, 42, 42};

	i = -1;
	while (++i < CANVAS_WIDTH)
	{
		put_pixel_canvas_rt(mrt, (t_pxl){i, 0}, c);
		put_pixel_canvas_rt(mrt, (t_pxl){-i, 0}, c);
		put_pixel_canvas_rt(mrt, (t_pxl){0, i}, c);
		put_pixel_canvas_rt(mrt, (t_pxl){0, -i}, c);
	}
}

void	init_cam(t_mrt mrt)
{
	t_camera	*cam;

	mrt.scene->cam = malloc(sizeof(t_camera));
	cam = mrt.scene->cam;
	cam->pos = v3_new(0, 0, -1);
	cam->look_at = v3_new(0, 0, 1);
	cam->fov = M_PI;
	cam->up = v3_new(0, 1, 0);
}

void	init_objs(t_mrt mrt)
{
	t_objlst	**objs;

	objs = &mrt.scene->objects;
	t_sphere	*sphere1 = malloc(sizeof(t_sphere));
	*sphere1 = (t_sphere){v3_new(0, 0, 10), 2, (t_colr){255, 0, 0}};
	t_sphere	*sphere2 = malloc(sizeof(t_sphere));
	*sphere2 = (t_sphere){v3_new(2, 0, 10), 2, (t_colr){0, 255, 0}};
	t_sphere	*sphere3 = malloc(sizeof(t_sphere));
	*sphere3 = (t_sphere){v3_new(-2, 0, 9), 1.5, (t_colr){0, 0, 142}};
	mrt.scene->objects = NULL;
	objlst_add_back(objs, objlst_new(SPHERE, sphere1));
	objlst_add_back(objs, objlst_new(SPHERE, sphere2));
	objlst_add_back(objs, objlst_new(SPHERE, sphere3));
}

void	init_scene(t_mrt mrt)
{
	init_objs(mrt);
	init_cam(mrt);
}

void	do_stuff(t_mrt mrt)
{
	show_sidebar(mrt);
	init_scene(mrt);
	print_scene(*mrt.scene);
	raytrace(mrt);
	draw_axis(mrt);
	objlst_clear(mrt.scene->objects);
}

