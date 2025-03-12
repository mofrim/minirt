/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_colr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:44:27 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/12 10:22:46 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Get the color of the found closest pixel. *This* is where all the future
 * magic will happen! */
t_colr	get_object_colr(t_scene scene, t_objlst *close_obj, t_v3 hitpoint)
{
	if (close_obj == NULL)
		return ((t_colr){0, 0, 0});
	if (close_obj->type == SPHERE)
		return (get_sphere_colr(scene, *(t_sphere *)close_obj->obj, hitpoint));
	return ((t_colr){0, 0, 0});
}

/**
 * Calculate the light intensity at the hitpoint.
 *
 * For the ambient light we use `colr_add_lights` which follows the
 * multiplication approach for color addition. The final obj_colr is calculated
 * using `colr_add_colr`. This is still to be justified technically. Optically
 * this works fine!
 * In the forumla for intensity calculation the surface normal is already
 * normalized -> |n| = 1 => we only devide by v3_norm(light_ray)!
 * `ip` := light [I]ntensity at hit[P]oint.
 */
// QUESTION Is this already working for all objects?!
t_colr	calculate_lights(t_scene scene, t_v3 hitpoint, t_v3 n, t_colr obj_colr)
{
	double		ip;
	double		ndotl;
	t_objlst	*objs;
	t_light		light;
	t_v3		light_ray;

	ip = scene.alight->bright;
	obj_colr = colr_add_light(obj_colr, colr_mult(scene.alight->colr, ip));
	objs = scene.objects;
	while (objs)
	{
		if (objs->type == LIGHT)
		{
			light = *(t_light *)objs->obj;
			light_ray = v3_add_vec(light.pos, v3_mult(hitpoint, -1));
			ndotl = v3_dot(n, light_ray);
			if (ndotl > 0)
			{
				ip = light.bright * ndotl / v3_norm(light_ray);
				obj_colr = colr_add_colr(obj_colr, colr_mult(light.colr, ip));
			}
		}
		objs = objs->next;
	}
	return (obj_colr);
}
