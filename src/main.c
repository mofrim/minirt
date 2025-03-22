/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:01:16 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/22 12:15:53 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_mrt		*mrt;
	t_scene		*scene;
	t_tokenizer *tokenizer;
	t_parser	*parser;

	if (ac != 2)
		return (printf("Usage: ./minirt SCENE_FILE\n"), 1);

	// Create a tokenizer with the scene file content
	tokenizer = tokenizer_new(av[1]); // Pass the scene file path to tokenizer_new
	if (!tokenizer)
		return (printf("Error creating tokenizer\n"), 1);

	// Create a parser with the tokenizer
	parser = parser_new(tokenizer);
	if (!parser)
		return (printf("Error creating parser\n"), 1);

	// Parse the scene using the parser
	scene = parser_parse(parser);
	if (!scene)
		return (printf("Error during scene file parsing\n"), 1);

	mrt = init_mrt(scene);
	mlx_key_hook(mrt->win, kbd_input_handler, mrt);
	mlx_hook(mrt->win, DestroyNotify, 0, close_btn_handler, mrt);
	do_stuff(*mrt);
	mlx_loop(mrt->mlx);
	tokenizer_free(tokenizer);
	parser_free(parser);
	cleanup_mrt(mrt);
	return (0);
}

// int	main(void)
// {
// 	t_colr a = {42, 42, 42};
// 	t_colr b = {0,0,100};
// 	t_colr c = colr_add_light(a, b);
// 	colr_print(c, "c");
//
// 	return (0);
// }
