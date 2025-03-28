/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:49:25 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/28 18:55:42 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool check_newline(t_tokenizer *tokenizer)
{
	int	pos;

	pos = tokenizer->position;
	skip_whitespace(tokenizer);
	if (tokenizer->input[tokenizer->position] == '\n')
	{
		tokenizer->position++;
		return (true);
	}
	tokenizer->position = pos;
	return (false);
}

static bool is_keyword(char *str)
{
    return (ft_strcmp(str, "A") == 0 || 
            ft_strcmp(str, "C") == 0 || 
            ft_strcmp(str, "L") == 0 || 
            ft_strcmp(str, "sp") == 0 || 
            ft_strcmp(str, "pl") == 0 || 
            ft_strcmp(str, "cy") == 0);
}

void parse_tokens_recursive(t_parser *parser, t_scene *scene, bool *valid)
{
    t_token *token;
    bool    element_parsed;

    element_parsed = false;
    token = tokenizer_next(parser->tokenizer);
    if (!token)
        return ;
    if (token->type == TOKEN_TYPE_KEYWORD)
    {
        if (!is_keyword(token->u_value.str))
        {
            ft_putendl_fd("Error\nInvalid element type", 2);
            *valid = false;
        }
        else
        {
            handle_token_keyword(parser, scene, token);
            element_parsed = true;
        }
    }
    token_free(token);
    if (!element_parsed)
        return ;

    if (!check_newline(parser->tokenizer))
    {
        ft_putendl_fd("Error\nMore than one element per line", 2);
        *valid = false;
        return ;
    }
    parse_tokens_recursive(parser, scene, valid);
}

