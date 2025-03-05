/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:33:53 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/05 14:02:39 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_scalar(struct s_vec3 *self, double d)
{
	self->x += d;
	self->y += d;
	self->z += d;
}

void add_vec(struct s_vec3 *self, struct s_vec3 v)
{
	self->x += v.x;
	self->y += v.y;
	self->z += v.z;
}

void add_vec_coords(struct s_vec3 *self, double x, double y, double z)
{
	self->x += x;
	self->y += y;
	self->z += z;
}

void	mult(struct s_vec3 *self, double d)
{
	self->x *= d;
	self->y *= d;
	self->z *= d;
}

t_vec3* vec3_new(double x, double y, double z)
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
    return (p);
}

