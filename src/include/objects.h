/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:36:20 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/08 10:49:25 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

#ifndef OBJECTS_H
# define OBJECTS_H

/* Object structs */
typedef enum e_obj
{
	PLANE,
	SPHERE,
	CYLINDER
} t_obj;

/* WARNING: the subject specifies that the *diameter* will be specified in the
 * scene.rt... still the radius is the number we will calculate with. this
 * means during parsing we need to devide the diameter read from the file by 2!
 */
typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	int		color[3];
} t_sphere;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	axis;
	double	radius;
	double	height;
} t_cylinder;

/* pop = Point On Plane :) */
typedef struct s_plane
{
	t_vec3	pop;
	t_vec3	normal;
	int		color[3];
} t_plane;

typedef struct s_amb_light
{
	double	ratio;
	int		color[3];
}	t_amb_light;

/* A first idea of a struct for the camera. */
typedef struct s_camera {
    t_vec3	position;
    t_vec3	look_at;
    t_vec3	up;
    double	fov;
    double	aspect_ratio;
}	t_camera;

/* The objects linked list. */
typedef struct s_objects
{
	t_obj				type;
	void				*data;
	struct s_objects	*next;
} t_objects;

#endif
