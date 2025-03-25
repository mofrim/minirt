/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:20:48 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/25 15:34:46 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double ft_atof(const char *str)
{
	double	res;
	int		sign;
	size_t	i;
	double	fract_part;
	double	fract_divisor;

	res = 0.0;
	i = 0;
	sign = 1;
	fract_part = 0.0;
	fract_divisor = 1.0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	
	while (i < ft_strlen(str) && ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}

	if (i < ft_strlen(str) && str[i] == '.')
	{
		i++;
		while (i < ft_strlen(str) && ft_isdigit(str[i]))
		{
			fract_part = fract_part * 10 + (str[i] - '0');
			fract_divisor *= 10;
			i++;
		}
	}
	return (sign * (res + fract_part / fract_divisor));
}

