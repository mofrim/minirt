/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:23:38 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/08 15:05:46 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_v3	canvas2viewport(int cx, int cy, double vw);
t_colr	traceray(t_objlst *objs, t_v3 campos, t_v3 d, double t_min, double t_max);
t_v2	intersectraysphere(t_v3 campos, t_v3 d, t_sphere *sphere);

void	raytrace(t_mrt mrt)
{
	int		cx;
	int		cy;
	t_v3	d;
	t_colr	px_colr;
	t_v3	campos;

	cx = PIXEL_MINX;
	campos = (t_v3){0, 0, 0};
	while (cx < PIXEL_MAXX)
	{
		cy = PIXEL_MINY;
		while (cy < PIXEL_MAXY)
		{
			d = canvas2viewport(cx, cy, 1.0);
			px_colr = traceray(mrt.scene->objects, campos, d, 1, 1000.0);
			put_pixel_canvas_rt(mrt, (t_pxl){cx, cy}, px_colr);
			cy++;
		}
		cx++;
	}
}


t_v3	canvas2viewport(int cx, int cy, double vw)
{ 
	t_v3	res;

	res.x = (double)cx * vw / CANVAS_WIDTH;
	res.y = (double)cy * vw / CANVAS_WIDTH;
	res.z = 1;
	return (res);
}

t_colr	traceray(t_objlst *objs, t_v3 campos, t_v3 d, double t_min, double t_max)
{
	double		closest_t;
	t_sphere	*closest_sphere;
	t_v2		t;

	closest_t = 1000000;
	closest_sphere = NULL;
	while (objs)
	{
		if (objs->type == SPHERE)
		{
			t = intersectraysphere(campos, d, objs->obj);
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

/* Highly not normified intersection calculation. 
 *
 * TODO: also the syntax for working with the t_vec3 is not at all comfy.
 * Possibilities:
 * 	1) either make the struct members in t_sphere directly t_vec3
 * 	2) drop t_vec3 completely in favor of external functions. Some pseudo-code
 * 	for this:
 *
 * 		co = v3_add_vec(co, v3_mult(center, -1));
 *
 * 	... IMHO this looks just much more clean to me.
 *
 * */
t_v2	intersectraysphere(t_v3 campos, t_v3 d, t_sphere *sphere)
{
	t_v2	res;
	double	r;
	t_vec3	co;
	t_vec3	center;
	t_vec3	d3;
	double a,b,c;
	double	disc;

	r = sphere->radius;
	co = vec3_new_v3(campos);
	center = vec3_new_v3(sphere->center);
	d3 = vec3_new_v3(d);
	co = co.add_vec(&co, center.mult(&center, -1));
	a = d3.dot(&d3, d3);
	b = 2 * co.dot(&co, d3);
	c = co.dot(&co, co) - r * r;
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return ((t_v2){1001.0, 1001.0});
	res.x1 = (-b + sqrt(disc) / (2 * a));
	res.x1 = (-b - sqrt(disc) / (2 * a));
	return (res);
}
