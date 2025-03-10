/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:23:38 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/10 09:49:40 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	canvas2viewport(int cx, int cy, double cvr);
t_colr	traceray(t_objlst *objs, t_v3 cam_pos, t_v3 d, double t_min, double t_max);
t_v2	intersectraysphere(t_v3 cam_pos, t_v3 d, t_sphere *sphere);

/**
 * The main raytracing routine.
 *
 * So far this is complete. Any further development should be happening in the
 * subroutines.
 */
void	raytrace(t_mrt mrt)
{
	int		cx;
	int		cy;
	t_v3	ray_dir;
	t_colr	px_colr;

	cx = PIXEL_MINX;
	px_colr = mrt.scene->alight->colr;
	while (cx < PIXEL_MAXX)
	{
		cy = PIXEL_MINY;
		while (cy < PIXEL_MAXY)
		{
			ray_dir = mtrx_prod_vec(mrt.scene->cam->rot,
					canvas2viewport(cx, cy, mrt.scene->cam->cvr));
			if (!(cy % mrt.scene->subsample))
				px_colr = traceray(mrt.scene->objects, mrt.scene->cam->pos,
						ray_dir, 1, INF);
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
 *
 * Explanation vor the calculation:
 * 	
 * 	The book says V_x = C_x * V_w/C_w and V_y = C_y * V_h / C_h, where V_x, V_y
 * 	are the corresponding viewport coords to the Canvas-coords C_x, C_y. V_w,
 * 	V_h and C_w,C_h are the viewport / Canvas width / height. In our case the
 * 	viewport height V_h = V_w * WINY / CANVAS_WIDTH = V_w * C_h / C_w
 * 	=> V_h/C_h  = V_w / C_w. So the same canvas_to_view_ratio =: cvr hast to be
 * 	applied to both coords.
 */
t_v3	canvas2viewport(int cx, int cy, double cvr)
{ 
	t_v3	viewport_vec;

	viewport_vec.x = (double)cx * cvr;
	viewport_vec.y = (double)cy * cvr;
	viewport_vec.z = 1;
	return (viewport_vec);
}

// TODO: make this work for several objects and intersections. So this will only
// return a `closest_obj` not a specific obj type.
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
