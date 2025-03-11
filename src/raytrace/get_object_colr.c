/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_colr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:44:27 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/11 09:10:49 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Get the color of the found closest pixel. *This* is where all the future
 * magic will happen! */
t_colr	get_object_colr(t_scene scene, t_objlst *close_obj, t_v3 ray_dir, double t)
{
	(void)ray_dir, (void)t, (void)scene;
	if (close_obj == NULL)
		return ((t_colr){0, 0, 0});
	if (close_obj->type == SPHERE)
	{
		return (((t_sphere *)close_obj->obj)->colr);
	}
	return ((t_colr){0, 0, 0});
}

t_colr	calculate_lights(t_objlst *objs, t_v3 p, t_v3 n, t_colr obj_colr)
{
	(void)obj_colr, (void)p, (void)n, (void)objs;
	return ((t_colr){0, 0, 0});
}
