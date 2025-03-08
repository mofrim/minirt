/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:35:39 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/08 18:44:52 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "src/include/minirt.h"

// Define the different types of tokens
typedef enum {
	TOKEN_TYPE_KEYWORD,
	TOKEN_TYPE_IDENTIFIER,
	TOKEN_TYPE_NUMBER,
	TOKEN_TYPE_SYMBOL,
} TokenType;

// Define the structure of a token
typedef struct {
	TokenType type;
	char *value;
} Token;

// Define the tokenizer
typedef struct {
	char *input;
	int position;
} Tokenizer;

// Create a new tokenizer
Tokenizer *tokenizer_new(char *input);

// Get the next token from the tokenizer
Token *tokenizer_next(Tokenizer *tokenizer);

// Free the tokenizer
void tokenizer_free(Tokenizer *tokenizer);

#endif