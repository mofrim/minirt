/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:49:45 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/10 09:42:24 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3_H
# define V3_H

/* A lighter 3d-vector struct. */
typedef struct s_v3
{
	double	x;
	double	y;
	double	z;
}	t_v3;

/* Creation. */
t_v3	*v3_new_alloc(double x, double y, double z);
t_v3	v3_new(double x, double y, double z);

/* Ops. */
t_v3	v3_add_scalar(t_v3 v, double d);
t_v3	v3_add_vec(t_v3 v, t_v3 w);
t_v3 	v3_add_vec_coords(t_v3 v, double x, double y, double z);
t_v3	v3_mult(t_v3 v, double d);
double	v3_dot(t_v3 v, t_v3 w);
t_v3	v3_cross(t_v3 v, t_v3 w);
double	v3_norm(t_v3 v);
t_v3	v3_get_norm(t_v3 v);

#endif
