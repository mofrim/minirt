/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:19:38 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/08 10:32:26 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*parse_scene(char *scene_file)
{
	/* For now go without scene file... */
	// int		sc_fd;
	// sc_fd = open(scene_file, O_RDONLY);
	// if (sc_fd == -1)
	// 	return (NULL);
	(void)scene_file;

	t_scene	*scene;
	scene = malloc(sizeof(t_scene));
	return (scene);
}
