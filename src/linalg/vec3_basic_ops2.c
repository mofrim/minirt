/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basic_ops2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:33:53 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/06 09:13:11 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	add_scalar(t_vec3 *self, double d)
{
	t_vec3	v;

	v = *self;
	v._add_scalar(&v, d);
	return (v);
}

t_vec3	add_vec(t_vec3 *self, t_vec3 w)
{
	t_vec3	v;

	v = *self;
	v._add_vec(&v, w);
	return (v);
}

t_vec3 add_vec_coords(t_vec3 *self, double x, double y, double z)
{
	t_vec3	v;

	v = *self;
	v._add_vec_coords(&v, x, y, z);
	return (v);
}

t_vec3	mult(t_vec3 *self, double d)
{
	t_vec3	v;

	v = *self;
	v._mult(&v, d);
	return (v);
}

/* Keep this around for maybe later use... */

// t_vec3	*add_scalar(t_vec3 *self, double d)
// {
// 	t_vec3	*v;
//
// 	v = vec3_new(self->x, self->y, self->z);
// 	v->_add_scalar(v, d);
// 	return (v);
// }
//
// t_vec3 *add_vec(t_vec3 *self, t_vec3 w)
// {
// 	t_vec3	*v;
//
// 	v = vec3_new(self->x, self->y, self->z);
// 	v->_add_vec(v, w);
// 	return (v);
// }
//
// t_vec3 *add_vec_coords(t_vec3 *self, double x, double y, double z)
// {
// 	t_vec3	*v;
//
// 	v = vec3_new(self->x, self->y, self->z);
// 	v->_add_vec_coords(v, x, y, z);
// 	return (v);
// }
//
// t_vec3	*mult(t_vec3 *self, double d)
// {
// 	t_vec3	*v;
//
// 	v = vec3_new(self->x, self->y, self->z);
// 	v->_mult(v, d);
// 	return (v);
// }

