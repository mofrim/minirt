/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:40:31 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/06 17:28:19 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Draw a disk. */
void	draw_disk(t_pxl p, int radius, char *colr, t_mrt mrt)
{
	int	i;
	int	j;

	i = -1;
	while (++i < radius)
	{
		j = -1;
		while (++j < sqrt(radius * radius - i * i))
		{
			put_pixel_canvas(mrt, (t_pxl){p.x - i, p.y + j}, colr);
			put_pixel_canvas(mrt, (t_pxl){p.x - i, p.y - j}, colr);
			put_pixel_canvas(mrt, (t_pxl){p.x + i, p.y + j}, colr);
			put_pixel_canvas(mrt, (t_pxl){p.x + i, p.y - j}, colr);
		}
	}
}
