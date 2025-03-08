/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:36:20 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/08 12:36:36 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "v3.h"

#ifndef OBJECTS_H
# define OBJECTS_H


/* The RGB color struct. */
typedef struct s_colr
{
	int	r;
	int	g;
	int	b;
}	t_colr;

/* Object structs */
typedef enum e_obj
{
	PLANE,
	SPHERE,
	CYLINDER
} t_objtype;

/* WARNING: the subject specifies that the *diameter* will be specified in the
 * scene.rt... still the radius is the number we will calculate with. this
 * means during parsing we need to devide the diameter read from the file by 2!
 */
typedef struct s_sphere
{
	t_v3	center;
	double	radius;
	t_colr	colr;
} t_sphere;

typedef struct s_cylinder
{
	t_v3	center;
	t_v3	axis;
	double	radius;
	double	height;
	t_colr	colr;
} t_cylinder;

/* pop = Point On Plane :) */
typedef struct s_plane
{
	t_v3	pop;
	t_v3	normal;
	t_colr	colr;
} t_plane;

typedef struct s_amb_light
{
	double	ratio;
	t_colr	colr;
}	t_amb_light;

/* Camera struct. */
typedef struct s_camera {
    t_v3	pos;
    t_v3	look_at;
    t_v3	up;
    double	fov;
}	t_camera;

/* The objects linked list. */
typedef struct s_objlst
{
	t_objtype		type;
	void			*obj;
	struct s_objlst	*next;
} t_objlst;

/********** Objlst llist funcs. **********/

t_objlst	*objlst_new(t_objtype type, void *obj);
t_objlst	*objlst_last(t_objlst *head);
void		objlst_add_back(t_objlst **head, t_objlst *newend);
void		objlst_clear(t_objlst *lst);
void		objlst_print(t_objlst *lst);

#endif
