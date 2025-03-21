/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:45:50 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/20 21:50:54 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XPM_H
# define XPM_H

# include "minirt.h"

typedef struct s_xpm_canvas
{
	t_xvar			*mlx;
	void			*img;
	unsigned char	*data;
	int				bpp;
	int				xpm_line_len;
	int				endian;
}	t_xpm_canvas;

t_xpm_canvas	*init_xpm_canvas(t_mrt mrt);
int				put_pixel_xpm(t_xpm_canvas *xc, int x, int y, t_colr colr);
t_xpm_canvas	*raytrace_xpm(t_mrt mrt);

#endif

