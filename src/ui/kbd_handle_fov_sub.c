/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kbd_handle_fov_sub.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:20:22 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/22 23:28:49 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Handle changes in subsampling via `{}` keys. */
void	handle_subsample(int key, t_mrt mrt)
{
	if (key == 91 && mrt.scene->subsample > 1)
	{
		mrt.scene->subsample -= 1;
		redraw_win(mrt);
	}
	else if (key == 93 && mrt.scene->subsample < 100)
	{
		mrt.scene->subsample++;
		redraw_win(mrt);
	}
}

/* Handle changes in fov via `()` keys. */
void	handle_fov(int key, t_mrt mrt)
{
	t_camera	*cam;

	cam = mrt.scene->cam;
	if (key == 57 && (cam->fov - 0.1 > 0))
	{
		cam->fov -= 0.1;
		cam->view_width = 2 * tan(cam->fov / 2);
		cam->cvr = cam->view_width / CANVAS_WIDTH;
		redraw_win(mrt);
	}
	if (key == 48 && (cam->fov + 0.1 < M_PI))
	{
		cam->fov += 0.1;
		cam->view_width = 2 * tan(cam->fov / 2);
		cam->cvr = cam->view_width / CANVAS_WIDTH;
		redraw_win(mrt);
	}
}
