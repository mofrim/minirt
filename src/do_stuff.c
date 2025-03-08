/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_stuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:29:11 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/08 12:50:25 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void draw_cross(t_mrt mrt)
{
	for (int i = 0;i < 100;i++) {
		put_pixel_canvas(mrt, (t_pxl){i, 0}, "00ff00");
		put_pixel_canvas(mrt, (t_pxl){-i, 0}, "00ff00");
		put_pixel_canvas(mrt, (t_pxl){0, i}, "00ff00");
		put_pixel_canvas(mrt, (t_pxl){0, -i}, "00ff00");
	}
}

// void	do_stuff(t_mrt mrt)
// {
// 	show_sidebar(mrt);
// 	draw_cross(mrt);
// 	draw_disk((t_pxl){0,0}, 10, "ff0000", mrt);
// 	draw_disk((t_pxl){-CANVAS_WIDTH/2,0}, 100, "ff0000", mrt);
// 	draw_disk((t_pxl){-CANVAS_WIDTH/2,WINY/2}, 123, "123458", mrt);
// 	draw_disk((t_pxl){CANVAS_WIDTH/2,WINY/2}, 123, "bbbbbb", mrt);
// 	draw_disk((t_pxl){CANVAS_WIDTH/2,WINY/2}, 123, "654321", mrt);
// 	draw_disk((t_pxl){CANVAS_WIDTH/4,WINY/4}, 123, "aaaa00", mrt);
// }

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
	*sphere1 = (t_sphere){v3_new(0, 0, 4.2), 4.2, (t_colr){42, 42, 42}};
	t_sphere	*sphere2 = malloc(sizeof(t_sphere));
	*sphere2 = (t_sphere){v3_new(2, 0, 2.1), 2.1, (t_colr){84, 84, 84}};
	mrt.scene->objects = NULL;
	objlst_add_back(objs, objlst_new(SPHERE, sphere1));
	objlst_add_back(objs, objlst_new(SPHERE, sphere2));
}

void	init_scene(t_mrt mrt)
{
	init_objs(mrt);
	init_cam(mrt);
}

void	do_stuff(t_mrt mrt)
{
	show_sidebar(mrt);
	draw_cross(mrt);
	init_scene(mrt);
	print_scene(*mrt.scene);
	objlst_clear(mrt.scene->objects);

}

