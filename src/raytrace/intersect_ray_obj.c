/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ray_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:29:10 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/17 21:26:47 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Returns the closest intersection found in all scene objects.
 *
 * This scans through all objects in the scene for a intersection. For the
 * object-dependent intersection calculations dispatches to the
 * intersect_ray_obj() func.
 * TODO: find better names!!!!
 */
t_intersec	intersect_ray_objs(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_objlst *objs)
{
	double		t;
	t_intersec	intersec;

	intersec.t = INF;
	intersec.obj = NULL;
	while (objs)
	{
		if (objs->type != LIGHT)
		{
			t = intersect_ray_obj(origin, ray_dir, rp, objs);
			if (rp.tmin < t && t < rp.tmax && t < intersec.t)
				intersec = (t_intersec){t, objs};
		}
		objs = objs->next;
	}
	return (intersec);
}

/* Generalized ray obj intersection function. Dispatches to the specific object
 * type intersection function. */
double	intersect_ray_obj(t_v3 origin, t_v3 ray_dir, t_ray_minmax rp,
		t_objlst *obj)
{
	if (obj->type == SPHERE)
		return (intersect_ray_sphere(origin, ray_dir, rp, obj->obj));
	return (0);
}
