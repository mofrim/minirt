/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:55:22 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/08 19:34:11 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_mrt	*mrt;
	t_scene	*scene;

	(void)ac;
	(void)av;
	// if (ac != 2)
	// 	return (printf("Usage: ./minirt SCENE_FILE\n"), 1);
	// scene = parse_scene(av[1]);
	scene = parse_scene("nofile");
	if (scene == NULL)
		return (printf("Error during scene file parsing\n"), 1);
	mrt = init_mrt(scene);
	mlx_key_hook(mrt->win, kbd_input_handler, mrt);
	mlx_hook(mrt->win, DestroyNotify, 0, close_btn_handler, mrt);
	do_stuff(*mrt);
	mlx_loop(mrt->mlx);
	return (0);
}

// int	main(void)
// {
// 	t_v3 v1 = v3_new(1,0,0);
// 	v1 = v3_add_scalar(v1, 4.2);
// 	printf("v1.x = %f, v1.y = %f, v1.z = %f\n", v1.x, v1.y, v1.z);
// 	printf("sizeof(t_v3) = %ld\n", sizeof(t_v3));
// 	return (0);
// }
