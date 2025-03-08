/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:55:22 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/08 11:48:57 by fmaurer          ###   ########.fr       */
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
// 	// t_vec3	*v;
// 	// t_vec3	w;
// 	//
// 	// v = vec3_new_alloc(1, 2, 3);
// 	// printf("x = %f, y = %f, z = %f\n", v->x, v->y, v->z);
// 	// v->_mult(v, 2);
// 	// printf("x = %f, y = %f, z = %f\n", v->x, v->y, v->z);
// 	// w = *v;
// 	// w._add_scalar(&w, 2);
// 	// printf("w.x = %f, w.y = %f, w.z = %f\n", w.x, w.y, w.z);
// 	// w._add_scalar(&w, 1.7);
// 	// printf("w.x = %f, w.y = %f, w.z = %f\n", w.x, w.y, w.z);
// 	//
// 	// t_vec3 u;
// 	// u = vec3_new(1, 1, 1);
// 	// u._add_scalar(&u, 1);
// 	// printf("u.x = %f, u.y = %f, u.z = %f\n", u.x, u.y, u.z);
// 	t_vec3 v1 = vec3_new(1,0,0);
// 	t_vec3 v2 = vec3_new(0,1,0);
// 	t_vec3 v3 = vec3_cross(v1, v2);
// 	printf("v1.x = %f, v1.y = %f, v1.z = %f\n", v1.x, v1.y, v1.z);
// 	printf("v2.x = %f, v2.y = %f, v2.z = %f\n", v2.x, v2.y, v2.z);
// 	printf("v3.x = %f, v3.y = %f, v3.z = %f\n", v3.x, v3.y, v3.z);
// 	printf("sizeof(t_vec3) = %ld\n", sizeof(t_vec3));
// 	return (0);
// }
