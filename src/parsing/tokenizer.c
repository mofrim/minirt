/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:36 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/22 12:10:22 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Create a new tokenizer
t_tokenizer *tokenizer_new(char *input)
{
	t_tokenizer *tokenizer = malloc(sizeof(t_tokenizer));
	if (!tokenizer)
		return NULL;
	tokenizer->input = input;
	tokenizer->position = 0;
	return tokenizer;
}

// Get the next token from the tokenizer
// t_token *tokenizer_next(t_tokenizer *tokenizer)
// {
//     // Skip whitespace
//     while (ft_isspace(tokenizer->input[tokenizer->position]))
//         tokenizer->position++;
//     // Check for end of input
//     if (tokenizer->input[tokenizer->position] == '\0')
//         return NULL;
//     // Create a new token
//     t_token *token = malloc(sizeof(t_token));
//     if (!token)
//         return NULL;
//     // Check for keyword
//     if (ft_isalpha(tokenizer->input[tokenizer->position]))
//     {
//         token->type = TOKEN_TYPE_KEYWORD;
//         token->u_value.str = parse_keyword(tokenizer);
//     }
//     // Check for identifier
//     else if (ft_isalpha(tokenizer->input[tokenizer->position]))
//     {
//         token->type = TOKEN_TYPE_IDENTIFIER;
//         token->u_value.str = parse_identifier(tokenizer);
//     }
//     // Check for number
//     else if (ft_isdigit(tokenizer->input[tokenizer->position]))
//     {
//         token->type = TOKEN_TYPE_NUMBER;
//         token->u_value.num = parse_number(tokenizer);
//     }
//     // Check for symbol
//     else
//     {
//         token->type = TOKEN_TYPE_SYMBOL;
//         token->u_value.str = parse_symbol(tokenizer);
//     }
//     return token;
// }

t_token *tokenizer_next(t_tokenizer *tokenizer) {
	// Skip whitespace
	while (tokenizer->input[tokenizer->position] && 
		   (tokenizer->input[tokenizer->position] == ' ' || 
			tokenizer->input[tokenizer->position] == '\t' || 
			tokenizer->input[tokenizer->position] == '\n'))
		tokenizer->position++;
	
	// Check for end of input
	if (tokenizer->input[tokenizer->position] == '\0')
		return NULL;
	
	// Create a new token
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return NULL;
	
	// Check if this is a coordinate or color triplet (like -50,0,20)
	if ((ft_isdigit(tokenizer->input[tokenizer->position]) || 
		 tokenizer->input[tokenizer->position] == '-' || 
		 tokenizer->input[tokenizer->position] == '+') &&
		ft_strchr(&tokenizer->input[tokenizer->position], ','))
	{
		// This is likely a coordinate or color triplet
		token->type = TOKEN_TYPE_KEYWORD;
		
		// Find where the triplet ends (at a space or newline)
		int start = tokenizer->position;
		while (tokenizer->input[tokenizer->position] && 
			   tokenizer->input[tokenizer->position] != ' ' && 
			   tokenizer->input[tokenizer->position] != '\t' && 
			   tokenizer->input[tokenizer->position] != '\n')
			tokenizer->position++;
		
		// Extract the triplet as a string
		token->u_value.str = ft_strndup(&tokenizer->input[start], 
									   tokenizer->position - start);
		
		return token;
	}
	// Check for a single letter identifier (like C, L, A)
	else if (ft_isalpha(tokenizer->input[tokenizer->position]))
	{
		int start = tokenizer->position;

		// If it's a single letter, or a two-letter identifier like "sp", "pl", "cy"
		if (ft_isalpha(tokenizer->input[tokenizer->position + 1]))
			tokenizer->position += 2;  // Two-letter identifier
		else
			tokenizer->position++;     // Single-letter identifier

		token->type = TOKEN_TYPE_KEYWORD;
		token->u_value.str = ft_strndup(&tokenizer->input[start], 
									   tokenizer->position - start);

		return token;
	}
	// Check for a numeric value
	else if (ft_isdigit(tokenizer->input[tokenizer->position]) || 
			 tokenizer->input[tokenizer->position] == '-' || 
			 tokenizer->input[tokenizer->position] == '+' || 
			 tokenizer->input[tokenizer->position] == '.')
	{
		int start = tokenizer->position;

		// Skip sign if present
		if (tokenizer->input[tokenizer->position] == '-' || 
			tokenizer->input[tokenizer->position] == '+')
			tokenizer->position++;

		// Parse digits
		while (ft_isdigit(tokenizer->input[tokenizer->position]))
			tokenizer->position++;

		// Parse decimal part if present
		if (tokenizer->input[tokenizer->position] == '.')
		{
			tokenizer->position++;
			while (ft_isdigit(tokenizer->input[tokenizer->position]))
				tokenizer->position++;
		}

		token->type = TOKEN_TYPE_NUMBER;

		// Extract and convert the number
		char *num_str = ft_strndup(&tokenizer->input[start], 
								  tokenizer->position - start);
		token->u_value.num = atof(num_str);  // Use ft_atof when implemented
		free(num_str);

		return token;
	}
	// Otherwise, it's probably a symbol
	else
	{
		token->type = TOKEN_TYPE_SYMBOL;
		token->u_value.str = ft_strndup(&tokenizer->input[tokenizer->position], 1);
		tokenizer->position++;

		return token;
	}
}






// Free the tokenizer
void tokenizer_free(t_tokenizer *tokenizer)
{
	free(tokenizer);
}

// Parse a keyword
char *parse_keyword(t_tokenizer *tokenizer)
{
	int start;
	start = tokenizer->position;
	while (ft_isalpha(tokenizer->input[tokenizer->position]))
		tokenizer->position++;
	return (ft_strndup(&tokenizer->input[start], tokenizer->position - start));
}

// Parse an identifier
char *parse_identifier(t_tokenizer *tokenizer)
{
	int start = tokenizer->position;
	while (ft_isalnum(tokenizer->input[tokenizer->position]))
		tokenizer->position++;
	return (ft_strndup(&tokenizer->input[start], tokenizer->position - start));
}

// Parse a number (needs refactoring, just for testing)
double parse_number(t_tokenizer *tokenizer)
{
	int start;
	int end;
	char *num_str;

	start = tokenizer->position;
	end = start;

	// Handle potential leading signs (+ or -)
	if (tokenizer->input[end] == '+' || tokenizer->input[end] == '-')
		end++;

	// Parse digits before the decimal point
	while (ft_isdigit(tokenizer->input[end]))
		end++;

	// Parse decimal point and digits after it
	if (tokenizer->input[end] == '.')
	{
		end++;
		while (ft_isdigit(tokenizer->input[end]))
		{
			end++;
		}
	}

	// skip commmas
	if (tokenizer->input[end] == ',')
		end++;

	// Extract the number string
	num_str = ft_strndup(&tokenizer->input[start], end - start);
	if (!num_str)
	{
		// Handle allocation error (return a default value or error)
		return (0.0); // Or handle the error as appropriate
	}

	// Convert the string to a double
	double num_value = atof(num_str);

	// Free the allocated string
	free(num_str);

	// Update tokenizer position
	tokenizer->position = end;

	return (num_value);
}

// Parse a symbol
char *parse_symbol(t_tokenizer *tokenizer)
{
	char *symbol = malloc(sizeof(char) * 2);
	if (!symbol)
		return NULL;
	symbol[0] = tokenizer->input[tokenizer->position++];
	symbol[1] = '\0';
	return (symbol);
}

