/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colr_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:32:55 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/22 22:12:19 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Multiply a colr by a double value. Avoid oveflow by maxing out to 255. */
t_colr	colr_mult(t_colr c, double i)
{
	t_colr	res;

	res.r = (c.r * i > 255) * 255 + (c.r * i <= 255) * (uint8_t)(c.r * i);
	res.g = (c.g * i > 255) * 255 + (c.g * i <= 255) * (uint8_t)(c.g * i);
	res.b = (c.b * i > 255) * 255 + (c.b * i <= 255) * (uint8_t)(c.b * i);
	return (res);
}

/* Add 2 colrs. Avoid oveflow by maxing out to 255. */
t_colr	colr_add_colr(t_colr c1, t_colr c2)
{
	t_colr	res;

	res.r = (c1.r + c2.r > 255) * 255 + (c1.r + c2.r <= 255) \
			* (uint8_t)(c1.r + c2.r);
	res.g = (c1.g + c2.g > 255) * 255 + (c1.g + c2.g <= 255) \
			* (uint8_t)(c1.g + c2.g);
	res.b = (c1.b + c2.b > 255) * 255 + (c1.b + c2.b <= 255) \
			* (uint8_t)(c1.b + c2.b);
	return (res);
}

/* Add a colr... and a light. Uses the multiplication approach which leads to a
 * very subtractive behavior. Meaning: If some value in your light is zero the
 * result for this value will also be zero here. */
// t_colr	colr_add_light(t_colr c, t_colr l)
// {
// 	t_colr	res;
// 	float	r;
// 	float	g;
// 	float	b;

// 	r = (c.r / 255.0f) * (l.r / 255.0f);
// 	g = (c.g / 255.0f) * (l.g / 255.0f);
// 	b = (c.b / 255.0f) * (l.b / 255.0f);
// 	res.r = (uint8_t)(r * 255);
// 	res.g = (uint8_t)(g * 255);
// 	res.b = (uint8_t)(b * 255);
// 	return (res);
// }

t_colr	colr_add_light(t_colr c, t_colr l)
{
	t_colr	res;
	float	color_blend;

	// Apply the light's color influence (we can adjust this factor, maybe
	// through the intensity?)
	color_blend = 0.7f; // How much the light color influences the object
	res.r = (uint8_t)fmin(255, c.r * (1.0f - color_blend + \
				color_blend * l.r / 255.0f));
	res.g = (uint8_t)fmin(255, c.g * (1.0f - color_blend + \
				color_blend * l.g / 255.0f));
	res.b = (uint8_t)fmin(255, c.b * (1.0f - color_blend + \
				color_blend * l.b / 255.0f));
	return (res);
}

/* Print a colr var and its name. */
void	colr_print(t_colr c, char *name)
{
	printf("colr-%s: [%d, %d, %d]\n", name, c.r, c.g, c.b);
}
