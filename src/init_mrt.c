/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:29:07 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/08 10:28:53 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_mlx_win(t_mrt *mrt);

t_mrt	*init_mrt(t_scene *scene)
{
	t_mrt	*mrt;

	mrt = malloc(sizeof(t_mrt));
	init_mlx_win(mrt);
	mrt->scene = scene;
	return (mrt);
}

static void	init_mlx_win(t_mrt *mrt)
{
	mrt->mlx = mlx_init();
	if (!mrt->mlx)
	{
		printf(" !! mlx_init fail !!\n");
		exit(1);
	}
	mrt->win = mlx_new_window(mrt->mlx, WINX, WINY, "minirt");
	if (!mrt->win)
	{
		printf("!! mlx_new_window fail !!\n");
		exit(1);
	}
}
