/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:30:43 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/05 18:32:07 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/vec3.h"
#include "minirt.h"

t_vec3 at(struct s_ray *self, double t)
{
	t_vec3	*v;

	v = vec3_new(self->orig.x, self->orig.y, self->orig.z);

    return ((t_vec3){
			self->orig.x + self->dir.x * t,
			self->orig.y + self->dir.y * t,
			self->orig.z + self->dir.z * t
			});
}

// t_ray* ray_new(t_vec3 orig, t_vec3 dir)
// {
//     t_ray *p = (t_ray *) malloc(sizeof(t_ray));
// 	p->dir =
//     p->at = at;
//     return (p);
// }
//
// // Destructor-like function
// void person_free(Person *p) {
//     free(p);
// }
