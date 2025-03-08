/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcolr_to_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:00:16 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/08 14:10:12 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Convert from RGB color in our t_colr type to int for mlx. */
int	tcolr_to_int(t_colr colr)
{
	int	red;
	int	green;
	int	blue;

	red = colr.r;
	green = colr.g;
	blue = colr.b;
	return (red << 16 | green << 8 | blue);
}

/* Convert from mlx's int-color to t_colr RGB color. */
t_colr	int_to_tcolr(int int_colr)
{
	t_colr	ret;

	ret.r = (int_colr >> 16) & 255;
	ret.g = (int_colr >> 8) & 255;
	ret.b = int_colr & 255;
	return (ret);
}
