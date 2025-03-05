/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:38:39 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/05 14:06:01 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

/* 3d vector. */
typedef struct s_vec3 {
    double	x;
	double	y;
	double	z;
	void (*add_scalar)(struct s_vec3 *self, double d);
	void (*add_vec)(struct s_vec3 *self, struct s_vec3 v);
	void (*add_vec_coords)(struct s_vec3 *self, double x, double y, double z);
	void (*mult)(struct s_vec3 *self, double d);
}	t_vec3;

t_vec3* vec3_new(double x, double y, double z);


#endif

