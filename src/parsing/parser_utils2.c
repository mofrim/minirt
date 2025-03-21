/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:52:15 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/22 22:53:06 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	parse_number(t_tokenizer *tokenizer)
{
	t_token	*token;
	double	value;

	token = parse_number_token(tokenizer);
	if (!token)
		return (0.0);

	value = token->u_value.num;
	token_free(token);
	return (value);
}
