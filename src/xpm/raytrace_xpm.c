/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_xpm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:23:38 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/20 21:49:22 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "xpm.h"

t_v3	canvas2viewport(int cx, int cy, t_camera cam);
t_colr	traceray(t_scene scene, t_v3 ray_dir);

t_xpm_canvas *raytrace_xpm(t_mrt mrt)
{
	int				cx;
	int				cy;
	t_v3			ray_dir;
	t_colr			px_colr;
	t_xpm_canvas	*xc;

	xc = init_xpm_canvas(mrt);
	cx = PIXEL_MINX;
	px_colr = mrt.scene->alight->colr;
	while (cx < PIXEL_MAXX)
	{
		cy = PIXEL_MINY;
		while (cy < PIXEL_MAXY)
		{
			ray_dir = canvas2viewport(cx, cy, *mrt.scene->cam);
			if (!(cy % mrt.scene->subsample))
				px_colr = traceray(*mrt.scene, ray_dir);
			put_pixel_xpm(xc, cx, cy, px_colr);
			cy++;
		}
		cx++;
	}
	return (xc);
}
