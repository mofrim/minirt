/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:33:53 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/06 17:36:30 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3* vec3_new_alloc(double x, double y, double z)
{
    t_vec3	*p;

	p = malloc(sizeof(t_vec3));
	p->x = x;
	p->y = y;
	p->z = z;
	p->add_scalar = add_scalar;
	p->add_vec = add_vec;
	p->add_vec_coords = add_vec_coords;
	p->mult = mult;
	p->dot = dot;
	p->cross = cross;
    return (p);
}

t_vec3 vec3_new(double x, double y, double z)
{
    t_vec3	p;

	p.x = x;
	p.y = y;
	p.z = z;
	p.add_scalar = add_scalar;
	p.add_vec = add_vec;
	p.add_vec_coords = add_vec_coords;
	p.mult = mult;
	p.dot = dot;
	p.cross = cross;
    return (p);
}
