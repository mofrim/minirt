/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_lights.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:01:17 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/17 21:44:50 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	calc_diff_reflection(t_light light, t_v3 light_ray, t_v3 n,
				t_colr *obj_colr);

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
 * NOTE: needed to go as low as 0.000001 with tmin for the shadow calculations
 * because otherwise there would be white pixels at some edgy places.
 */
// QUESTION Is this already working for all objects?!
t_colr	calculate_lights(t_scene scene, t_v3 hitpoint, t_v3 n, t_colr obj_colr)
{
	t_objlst	*objs;
	t_light		light;
	t_v3		light_ray;

	obj_colr = colr_add_light(obj_colr, \
			colr_mult(scene.alight->colr, scene.alight->bright));
	objs = scene.objects;
	while (objs)
	{
		if (objs->type == LIGHT)
		{
			light = *(t_light *)objs->obj;
			light_ray = v3_add_vec(light.pos, v3_mult(hitpoint, -1));
			if (intersect_ray_objs(hitpoint, light_ray, \
					(t_ray_minmax){0.000001, 1.0}, scene.objects).t == INF)
				calc_diff_reflection(light, light_ray, n, &obj_colr);
		}
		objs = objs->next;
	}
	return (obj_colr);
}

/* Extracted diffuse reflection calculation routine. */
void	calc_diff_reflection(t_light light, t_v3 light_ray, t_v3 n,
		t_colr *obj_colr)
{
	double	ndotl;
	double	ip;

	ndotl = v3_dot(n, light_ray);
	if (ndotl > 0)
	{
		ip = light.bright * ndotl / v3_norm(light_ray);
		*obj_colr = colr_add_colr(*obj_colr, colr_mult(light.colr, ip));
	}
}
