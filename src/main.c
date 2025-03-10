/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:55:22 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/10 09:46:58 by fmaurer          ###   ########.fr       */
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
// 	t_mtrx a = get_rotmtrx(v3_get_norm((t_v3){0, -5, 10}));
// 	mtrx_print(a);
// 	return (0);
// }
