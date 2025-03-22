/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:33:27 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/22 11:39:43 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "xpm.h"

/**
 * Init xpm canvas and check endianess.
 *
 * Once again: 'big endian' = most significant bit goes first, 'little endian' =
 * least significant bit first. I.e. 0x11223344 -> 11223344 in big endian mem
 * vs. 44332211 in little endian mem.
 * TODO: explain members, esp. `opp` and `bpp`
 */
t_xpm_canvas	*init_xpm_canvas(t_xvar *mlx)
{
	t_xpm_canvas	*xcanv;
	int				bpp;
	int				xl;
	int				endian;
	int				a;

	xcanv = malloc(sizeof(t_xpm_canvas));
	xcanv->mlx = mlx;
	xcanv->img = mlx_new_image(mlx, CANVAS_WIDTH, WINY);
	xcanv->data = (unsigned char *)mlx_get_data_addr(xcanv->img, &bpp, &xl,
			&endian);
	xcanv->bpp = bpp;
	xcanv->opp = bpp / 8;
	xcanv->xpm_line_len = xl;
	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		xcanv->endian = 1;
	else
		xcanv->endian = 0;
	return (xcanv);
}

int	put_pixel_xpm(t_xpm_canvas *xc, int x, int y, t_colr colr)
{
	int				dec;
	int				color;
	unsigned char	*ptr;

	if (x > PIXEL_MAXX || y > PIXEL_MAXY)
		return (-1);
	ptr = &xc->data[(PIXEL_MAXY - y) * xc->xpm_line_len];
	color = mlx_get_color_value(xc->mlx, tcolr_to_int(colr));
	dec = xc->opp;
	while (dec--)
		*(ptr + (PIXEL_MAXX + x) * xc->opp + dec) = \
			((unsigned char *)(&color))[dec];
	return (0);
}
