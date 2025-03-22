/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:35:13 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/22 15:46:27 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Add this to the setup_scene function or wherever appropriate
void	setup_scene(t_scene *scene)
{
	// Set up camera
	if (scene->cam)
		setup_camera(scene->cam);
	// Create default ambient light if none exists
	if (!scene->alight)
	{
		scene->alight = malloc(sizeof(t_amb_light));
		if (scene->alight)
		{
			scene->alight->bright = 0.2;
			scene->alight->colr = (t_colr){255, 255, 255};
			ft_printf
			("Created def ambient light: bright=%f, color=(%d,%d,%d)\n",
					scene->alight->bright, scene->alight->colr.r,
					scene->alight->colr.g, scene->alight->colr.b);
		}
	}
	// Check if any objects exist
	if (!scene->objects)
	{
		ft_printf("Warning: No objects in scene!\n");
	}
}
