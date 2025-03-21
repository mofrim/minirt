/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:35:13 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/21 18:38:16 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_scene(t_scene *scene)
{
	if (!scene)
		return ;
	
	setup_camera(scene->cam);

	scene->subsample = 1;

	if (!scene->alight)
	{
		scene->alight = malloc(sizeof(t_amb_light));
		if (scene->alight)
		{
			scene->alight->bright = 0.2; // default val
			scene->alight->colr = (t_colr){255, 255, 255}; // default white
		}
	}
}