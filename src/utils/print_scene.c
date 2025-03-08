/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:43:57 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/08 12:50:56 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_cam(t_camera cam)
{
	printf("  pos=(%f,%f,%f), look_at=(%f,%f,%f), fov=%f\n",
			cam.pos.x, cam.pos.x, cam.pos.x,
			cam.look_at.x, cam.look_at.x, cam.look_at.x,
			cam.fov);
}

void	print_scene(t_scene scene)
{
	printf("-- cam --\n");
	print_cam(*scene.cam);
	printf("-- objects --\n");
	objlst_print(scene.objects);
}
