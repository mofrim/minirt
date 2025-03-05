/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:55:22 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/05 09:15:50 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_mrt	*mrt;
	t_scene	*scene;

	(void)av;
	(void)ac;
	if (ac != 2)
		return (printf("Usage: ./minirt SCENE_FILE\n"), 1);

	scene = parse_scene(av[1]);
	if (scene == NULL)
		return (printf("Error during scene file parsing\n"), 1);
	mrt = init_mrt();
	mlx_key_hook(mrt->win, kbd_input_handler, mrt);
	mlx_hook(mrt->win, DestroyNotify, 0, close_btn_handler, mrt);
	mlx_string_put(mrt->mlx, mrt->win, WINX/2-40, WINY/2, rgb_to_int("00ff00"),
			"MiniRT coming soon...");
	mlx_loop(mrt->mlx);
	return (0);
}
