/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:23:38 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/09 09:51:54 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	canvas2viewport(int cx, int cy, double cvr);
t_colr	traceray(t_objlst *objs, t_v3 cam_pos, t_v3 d, double t_min, double t_max);
t_v2	intersectraysphere(t_v3 cam_pos, t_v3 d, t_sphere *sphere);

// TODOs:
// 1) implement the camera to obey the FOV input param from the scene file
// 2) implement resolution setting

void	raytrace(t_mrt mrt)
{
	int		cx;
	int		cy;
	t_v3	d;
	t_colr	px_colr;

	cx = PIXEL_MINX;
	px_colr = mrt.scene->alight->colr;
	while (cx < PIXEL_MAXX)
	{
		cy = PIXEL_MINY;
		while (cy < PIXEL_MAXY)
		{
			d = canvas2viewport(cx, cy, mrt.scene->cam->canvas_to_view_ratio);
			if (!(cy % mrt.scene->subsample))
				px_colr = traceray(mrt.scene->objects, mrt.scene->cam->pos, d, 1, INF);
			put_pixel_canvas_rt(mrt, (t_pxl){cx, cy}, px_colr);
			cy++;
		}
		cx++;
	}
}


/**
 * Converts canvas coords to viewport coords.
 *
 * The Screen coordinates (params cx and cy) are given in our raytracing-canvas
 * coordinates where the middle of the canvas is the origin. The 2nd param is
 * the canvas2viewport_ratio.
 * We always want our viewport to be at a 1 unit distance from our camera ->
 * z = 1.
 */
// QUESTION: where to implement a `resolution` or `dpi` notion in here???
// it must be somehwere
// QUESTION: why does it work like that?!?!?!?! I mean: why dividing by ratio
// yields the correct ascpect?
t_v3	canvas2viewport(int cx, int cy, double canvas_to_viewport_ratio)
{ 
	t_v3	viewport_vec;

	viewport_vec.x = (double)cx * canvas_to_viewport_ratio;
	viewport_vec.y = (double)cy * canvas_to_viewport_ratio;
	viewport_vec.z = 1;
	return (viewport_vec);
}

t_colr	traceray(t_objlst *objs, t_v3 cam_pos, t_v3 d, double t_min, double t_max)
{
	double		closest_t;
	t_sphere	*closest_sphere;
	t_v2		t;

	closest_t = INF;
	closest_sphere = NULL;
	while (objs)
	{
		if (objs->type == SPHERE)
		{
			t = intersectraysphere(cam_pos, d, objs->obj);
			if (t_min < t.x1 && t.x1 < t_max && t.x1 < closest_t)
			{
				closest_t = t.x1;
				closest_sphere = objs->obj;
			}
			if (t_min < t.x2 && t.x2 < t_max && t.x2 < closest_t)
			{
				closest_t = t.x2;
				closest_sphere = objs->obj;
			}
		}
		objs = objs->next;
	}
	if (closest_sphere == NULL)
		return ((t_colr){0, 0, 0});
	return (closest_sphere->colr);
}

/* The intersection of the ray with the object. The heart of raytracing. */
t_v2	intersectraysphere(t_v3 cam_pos, t_v3 d, t_sphere *sphere)
{
	t_v2	res;
	t_v3	co;
	t_v3	abc;
	double	disc;

	co = v3_add_vec(cam_pos, v3_mult(sphere->center, -1));
	abc.x = v3_dot(d, d);
	abc.y = 2 * v3_dot(co, d);
	abc.z = v3_dot(co, co) - sphere->r_squared;
	disc = abc.y * abc.y - 4 * abc.x * abc.z;
	if (disc < 0)
		return ((t_v2){INF, INF});
	res.x1 = (-abc.y + sqrt(disc) / (2 * abc.x));
	res.x1 = (-abc.y - sqrt(disc) / (2 * abc.x));
	return (res);
}
