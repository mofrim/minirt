/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:49:45 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/08 14:30:10 by fmaurer          ###   ########.fr       */
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

t_v3	*v3_new_alloc(double x, double y, double z);
t_v3	v3_new(double x, double y, double z);

#endif
