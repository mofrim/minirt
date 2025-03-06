/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:38:39 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/06 10:00:00 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

/* 3d vector class.. struct. */
typedef struct s_vec3 {
	double			x;
	double			y;
	double			z;
	struct s_vec3	(*_add_scalar)(struct s_vec3 *self, double d);
	struct s_vec3	(*_add_vec)(struct s_vec3 *self, struct s_vec3 v);
	struct s_vec3	(*_add_vec_coords)(struct s_vec3 *self, double x, double y,
			double z);
	struct s_vec3	(*_mult)(struct s_vec3 *self, double d);
	struct s_vec3	(*add_scalar)(struct s_vec3 *self, double d);
	struct s_vec3	(*add_vec)(struct s_vec3 *self, struct s_vec3 v);
	struct s_vec3	(*add_vec_coords)(struct s_vec3 *self, double x, double y,
			double z);
	struct s_vec3	(*mult)(struct s_vec3 *self, double d);
	double			(*dot)(struct s_vec3 *self, struct s_vec3 w);
	struct s_vec3	(*cross)(struct s_vec3 *self, struct s_vec3 w);
}	t_vec3;

/* Class functions changing the vector. */
t_vec3	_add_scalar(t_vec3 *self, double d);
t_vec3	_add_vec(t_vec3 *self, t_vec3 v);
t_vec3	_add_vec_coords(t_vec3 *self, double x, double y, double z);
t_vec3	_mult(t_vec3 *self, double d);

/* Class functions only returning the result. */
t_vec3	add_scalar(t_vec3 *self, double d);
t_vec3	add_vec(t_vec3 *self, t_vec3 w);
t_vec3	add_vec_coords(t_vec3 *self, double x, double y, double z);
t_vec3	mult(t_vec3 *self, double d);


/* Dot and cross products. */
/* Class functions. */
double	dot(t_vec3 *self, t_vec3 w);
t_vec3	cross(t_vec3 *self, t_vec3 w);
/* External functions. */
t_vec3	vec3_cross(t_vec3 u, t_vec3 w);
double	vec3_dot(t_vec3 v, t_vec3 w);
t_vec3	*vec3_cross_alloc(t_vec3 u, t_vec3 w);

t_vec3	vec3_new(double x, double y, double z);
t_vec3	*vec3_new_alloc(double x, double y, double z);

#endif
