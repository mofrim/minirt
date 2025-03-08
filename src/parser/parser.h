/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:22:49 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/08 19:03:04 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"

// Define the different types of nodes in the AST
typedef enum {
    NODE_TYPE_SCENE,
    NODE_TYPE_AMBIENT_LIGHT,
    NODE_TYPE_CAMERA,
    NODE_TYPE_LIGHT,
    NODE_TYPE_SPHERE,
    NODE_TYPE_PLANE,
    NODE_TYPE_CYLINDER,
} NodeType;

// Define the structure of a node in the AST
typedef struct s_node {
    NodeType    type;
    t_camera    camera;
    t_amb_light alight;
    t_sphere    sphere;
    t_plane     plane;
    t_cylinder  cylinder;
    struct s_node *next; // For sibling nodes (no need for children)
}   t_node;

// Define the parser
typedef struct {
    Tokenizer *tokenizer;
} Parser;

// Create a new parser
Parser *parser_new(Tokenizer *tokenizer);

// Parse the stream of tokens and return the AST
Node *parser_parse(Parser *parser);

// Free the parser
void parser_free(Parser *parser);

#endif