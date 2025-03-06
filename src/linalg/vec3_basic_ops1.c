/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basic_ops1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:33:53 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/06 08:14:32 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	_add_scalar(t_vec3 *self, double d)
{
	self->x += d;
	self->y += d;
	self->z += d;
	return (*self);
}

t_vec3 _add_vec(t_vec3 *self, t_vec3 v)
{
	self->x += v.x;
	self->y += v.y;
	self->z += v.z;
	return (*self);
}

t_vec3 _add_vec_coords(t_vec3 *self, double x, double y, double z)
{
	self->x += x;
	self->y += y;
	self->z += z;
	return (*self);
}

t_vec3	_mult(t_vec3 *self, double d)
{
	self->x *= d;
	self->y *= d;
	self->z *= d;
	return (*self);
}
