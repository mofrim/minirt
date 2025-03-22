/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_mrt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:11:23 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/22 16:45:54 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cleanup_mrt(t_mrt *mrt)
{
	mlx_destroy_image(mrt->mlx, mrt->xc->img);
	mlx_destroy_window(mrt->mlx, mrt->win);
	mlx_destroy_display(mrt->mlx);
	free(mrt->xc);
	free(mrt->mlx);
	objlst_clear(mrt->scene->objects);
	free(mrt->scene->cam);
	free(mrt->scene->alight);
	free(mrt->scene);
	free(mrt);
}
