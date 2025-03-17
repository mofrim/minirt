/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_colr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:16:01 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/17 19:16:39 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Returns the normal vector on the sphere at a given hitpoint. */
t_v3	get_normal_sphere(t_v3	hitpoint, t_v3 center)
{
	return (v3_get_norm(v3_add_vec(hitpoint, v3_mult(center, -1))));
}

/* Returns the color of the sphere at the hitpoint. So far only for ambient and
 * diffuse lighting. */
t_colr	get_sphere_colr(t_scene scene, t_sphere s, t_v3 hitpoint)
{
	t_v3	normal_vec;
	t_colr	colr_at_hitpoint;

	normal_vec = get_normal_sphere(hitpoint, s.center);
	colr_at_hitpoint = calculate_lights(scene, hitpoint, normal_vec, s.colr);
	return (colr_at_hitpoint);
}
