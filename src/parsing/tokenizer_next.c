/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_next.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:36 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/24 11:15:58 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_coordinate(t_tokenizer *tokenizer)
{
	bool	is_really_v3;
	size_t		i;

	i = 0;
	while (tokenizer->position + i < tokenizer->len && \
				!ft_isspace(tokenizer->input[tokenizer->position + i]))
		i++;
	is_really_v3 = (ft_strchr(&tokenizer->input[tokenizer->position], ',') - &tokenizer->input[tokenizer->position]) < (int)i;
	return (is_really_v3 && (ft_isdigit(tokenizer->input[tokenizer->position]) || \
			tokenizer->input[tokenizer->position] == '-' || \
			tokenizer->input[tokenizer->position] == '+'));
}

int	is_identifier(t_tokenizer *tokenizer)
{
	return (ft_isalpha(tokenizer->input[tokenizer->position]));
}

int	is_numeric(t_tokenizer *tokenizer)
{
	return (ft_isdigit(tokenizer->input[tokenizer->position]) || \
				tokenizer->input[tokenizer->position] == '-' || \
				tokenizer->input[tokenizer->position] == '+' || \
			tokenizer->input[tokenizer->position] == '.');
}

t_token	*tokenizer_next(t_tokenizer *tokenizer)
{
	skip_whitespace(tokenizer);
	if (tokenizer->input[tokenizer->position] == '\0')
		return (NULL);
	if (is_coordinate(tokenizer))
		return (parse_coordinate(tokenizer));
	else if (is_identifier(tokenizer))
		return (parse_identifier(tokenizer));
	else if (is_numeric(tokenizer))
		return (parse_number_token(tokenizer));
	else
		return (parse_symbol_token(tokenizer));
}

char	*parse_keyword(t_tokenizer *tokenizer)
{
	int	start;

	start = tokenizer->position;
	while (ft_isalpha(tokenizer->input[tokenizer->position]))
		tokenizer->position++;
	return (ft_strndup(&tokenizer->input[start], tokenizer->position - start));
}
