/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:33:27 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/20 22:10:28 by fmaurer          ###   ########.fr       */
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
 */
t_xpm_canvas	*init_xpm_canvas(t_mrt mrt)
{
	t_xpm_canvas	*xcanv;
	int				bpp;
	int				xl;
	int				endian;
	int				a;

	xcanv = malloc(sizeof(t_xpm_canvas));
	xcanv->mlx = mrt.mlx;
	xcanv->img = mlx_new_image(mrt.mlx, CANVAS_WIDTH, WINY);
	xcanv->data = (unsigned char *)mlx_get_data_addr(xcanv->img, &bpp, &xl,
			&endian);
	xcanv->bpp = bpp;
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
  int			opp;
  int			dec;
  int			color;
  unsigned char	*ptr;

  if (x > PIXEL_MAXX || y > PIXEL_MAXY)
	  return (-1);
  opp = xc->bpp/8; // with 32 bits opp == 4
  ptr = &xc->data[(PIXEL_MAXY - y) * xc->xpm_line_len];
  color = mlx_get_color_value(xc->mlx, tcolr_to_int(colr));
  dec = opp;
  while (dec--)
	  *(ptr+(PIXEL_MAXX + x) * opp + dec) = ((unsigned char *)(&color))[dec];
  return (0);
}
