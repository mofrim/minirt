/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_stuff-2spheres-shadow_colored_lights.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:29:11 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/17 19:58:32 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// QUESTION: is this really correct? I mean the visualization?

#include "minirt.h"

void	init_cam(t_mrt mrt)
{
	t_camera	*cam;

	mrt.scene->cam = malloc(sizeof(t_camera));
	cam = mrt.scene->cam;
	cam->pos = v3_new(-5, 0, -3);
	cam->orient = v3_new(1, 0, 1);
	cam->fov = M_PI_4;
	cam->rot = get_rotmtrx(v3_get_norm(cam->orient));
	cam->view_width = 2 * tan(cam->fov/2);
	cam->cvr = cam->view_width / CANVAS_WIDTH;
}

void	init_objs(t_mrt mrt)
{
	t_objlst	**objs;

	mrt.scene->objects = NULL;
	objs = &mrt.scene->objects;

	t_sphere	*sphere1 = malloc(sizeof(t_sphere));
	*sphere1 = (t_sphere){v3_new(0, 0, 10), 2, 2 * 2, (t_colr){255, 0, 0}};
	t_sphere	*sphere2 = malloc(sizeof(t_sphere));
	*sphere2 = (t_sphere){v3_new(0, 0, 4), 0.5, 0.25, (t_colr){0, 255, 0}};
	// t_sphere	*sphere3 = malloc(sizeof(t_sphere));
	// *sphere3 = (t_sphere){v3_new(1, 0, -6.12), 0.1, 0.01, (t_colr){255, 255, 255}};
	// t_sphere	*sphere4 = malloc(sizeof(t_sphere));
	// *sphere4 = (t_sphere){v3_new(-1, 0, -6.12), 0.1, 0.01, (t_colr){255, 255, 255}};
	objlst_add_back(objs, objlst_new(SPHERE, sphere1));
	objlst_add_back(objs, objlst_new(SPHERE, sphere2));
	// objlst_add_back(objs, objlst_new(SPHERE, sphere3));
	// objlst_add_back(objs, objlst_new(SPHERE, sphere4));
}

void	init_lights(t_mrt mrt)
{
	t_objlst	**objs;

	mrt.scene->alight = malloc(sizeof(t_amb_light));
	mrt.scene->alight->bright = 0.4;
	mrt.scene->alight->colr = (t_colr){255, 255, 255};

	objs = &mrt.scene->objects;

	t_light	*light1 = malloc(sizeof(t_light));
	light1->bright = 0.8;
	light1->colr = (t_colr){0, 120, 0};
	light1->pos = (t_v3){1, 0, -6};
	objlst_add_back(objs, objlst_new(LIGHT, light1));

	t_light	*light2 = malloc(sizeof(t_light));
	light2->bright = 0.8;
	light2->colr = (t_colr){0, 0, 120};
	light2->pos = (t_v3){-1, 0, -6};
	objlst_add_back(objs, objlst_new(LIGHT, light2));
}

void	init_scene(t_mrt mrt)
{
	init_objs(mrt);
	init_cam(mrt);
	init_lights(mrt);
	mrt.scene->subsample = 1;
}

void	do_stuff(t_mrt mrt)
{
	init_scene(mrt);
	show_sidebar(mrt);
	print_scene(*mrt.scene);
	raytrace(mrt);
	// draw_axis(mrt);
}

