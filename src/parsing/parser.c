/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:35:22 by jroseiro          #+#    #+#             */
/*   Updated: 2025/03/22 13:01:32 by jroseiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Create a new parser
t_parser	*parser_new(t_tokenizer *tokenizer)
{
	t_parser *parser = malloc(sizeof(t_parser));
	if (!parser)
		return NULL;
	parser->tokenizer = tokenizer;
	return parser;
}

// Parse the stream of tokens and return the scene
t_scene	*parser_parse(t_parser *parser)
{
	t_scene		*scene;
	t_token		*token;
	t_objlst	*objlst;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL); // Handle allocation error
	scene->objects = NULL; // Initialize objects list
	scene->alight = NULL;
	scene->cam = NULL;
	scene->subsample = 1;

	while ((token = tokenizer_next(parser->tokenizer)) != NULL)
	{
		if (token->type == TOKEN_TYPE_KEYWORD)
		{
			if (strcmp(token->u_value.str, "A") == 0)
				scene->alight = parse_ambient_light(parser);
			else if (strcmp(token->u_value.str, "C") == 0)
				scene->cam = parse_camera(parser);
			else if (strcmp(token->u_value.str, "L") == 0)
			{
				objlst = objlst_new(LIGHT, parse_light(parser));
				objlst_add_back(&scene->objects, objlst);
			}
			else if (strcmp(token->u_value.str, "sp") == 0)
			{
				objlst = objlst_new(SPHERE, parse_sphere(parser));
				objlst_add_back(&scene->objects, objlst);
			}
			else if (strcmp(token->u_value.str, "pl") == 0)
			{
				objlst = objlst_new(PLANE, parse_plane(parser));
				objlst_add_back(&scene->objects, objlst);
			}
			else if (strcmp(token->u_value.str, "cy") == 0)
			{
				objlst = objlst_new(CYLINDER, parse_cylinder(parser));
				objlst_add_back(&scene->objects, objlst);
			}
			else
			{
				// Handle invalid keyword
			}
		}
		else
		{
			// Handle unexpected token
		}
		token_free(token);
	}
	return scene;
}

// Free the parser
void	parser_free(t_parser *parser)
{
	free(parser);
}

// Parse the ambient light
t_amb_light	*parse_ambient_light(t_parser *parser)
{
	t_amb_light	*amb_light;

	amb_light = malloc(sizeof(t_amb_light));
	if (!amb_light)
		return (NULL); // Handle allocation error
	amb_light->bright = parse_number(parser->tokenizer);
	amb_light->colr = parse_color(parser);
	return amb_light;
}


// Parse the camera
// t_camera	*parse_camera(t_parser *parser)
// {
// 	t_camera *camera;

// 	camera = malloc(sizeof(t_camera));
// 	if (!camera)
// 		return (NULL); // Handle allocation error
// 	camera->pos = parse_v3(parser);
// 	camera->orient = parse_v3(parser);
// 	camera->fov = parse_number(parser->tokenizer);
// 	return camera;
// }

/******* test *******/
t_camera *parse_camera(t_parser *parser)
{
	t_camera *camera;
	t_token *token;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->pos = parse_v3(parser);
	camera->orient = parse_v3(parser);

	// Get FOV token and convert it to a number
	token = tokenizer_next(parser->tokenizer);
	if (token && token->type == TOKEN_TYPE_NUMBER)
	{
		camera->fov = token->u_value.num;
		token_free(token);
	}
	else 
	{
		// Default FOV value if parsing fails
		camera->fov = 70.0;
		if (token) token_free(token);
	}

	return (camera);
}



// Parse a light
// t_light *parse_light(t_parser *parser)
// {
// 	t_light *light = malloc(sizeof(t_light));

// 	if (!light)
// 		return (NULL); // Handle allocation error
// 	light->pos = parse_v3(parser);
// 	light->bright = parse_number(parser->tokenizer);
// 	light->colr = parse_color(parser);
// 	return light;
// }

// test
t_light *parse_light(t_parser *parser)
{
	t_light *light = malloc(sizeof(t_light));
	t_token *token;

	if (!light)
		return (NULL);
	
	// Parse position
	light->pos = parse_v3(parser);
	
	// Get brightness token
	token = tokenizer_next(parser->tokenizer);
	if (token && token->type == TOKEN_TYPE_KEYWORD) {
		// If it came as a string (like "0.7")
		light->bright = atof(token->u_value.str);
	} else if (token && token->type == TOKEN_TYPE_NUMBER) {
		// If it came as a number
		light->bright = token->u_value.num;
	} else {
		// Default value if parsing fails
		light->bright = 0.7;
	}
	
	if (token)
		token_free(token);
	
	// Parse color
	light->colr = parse_color(parser);
	
	printf("Created light: pos=(%f,%f,%f), brightness=%f, color=(%d,%d,%d)\n",
		   light->pos.x, light->pos.y, light->pos.z, 
		   light->bright, light->colr.r, light->colr.g, light->colr.b);
	
	return light;
}


//Parse a sphere
// t_sphere *parse_sphere(t_parser *parser)
// {
// 	t_sphere *sphere = malloc(sizeof(t_sphere));

// 	if (!sphere)
// 		return (NULL); // Handle allocation error
// 	sphere->center = parse_v3(parser);
// 	sphere->r_squared = parse_number(parser->tokenizer);
// 	sphere->colr = parse_color(parser);
// 	return sphere;
// }

t_sphere *parse_sphere(t_parser *parser)
{
	t_sphere *sphere = malloc(sizeof(t_sphere));
	t_token *token;

	if (!sphere)
		return (NULL);
	
	// Parse center
	sphere->center = parse_v3(parser);
	
	// Get diameter token and convert to radius
	token = tokenizer_next(parser->tokenizer);
	if (token && token->type == TOKEN_TYPE_KEYWORD) {
		// If it came as a string (like "20")
		double diameter = atof(token->u_value.str);
		sphere->r = diameter / 2.0;
		sphere->r_squared = sphere->r * sphere->r;
	} else if (token && token->type == TOKEN_TYPE_NUMBER) {
		// If it came as a number
		double diameter = token->u_value.num;
		sphere->r = diameter / 2.0;
		sphere->r_squared = sphere->r * sphere->r;
	} else {
		// Default values if parsing fails
		sphere->r = 1.0;
		sphere->r_squared = 1.0;
	}
	
	if (token)
		token_free(token);
	
	// Parse color
	sphere->colr = parse_color(parser);
	
	printf("Created sphere: center=(%f,%f,%f), radius=%f, color=(%d,%d,%d)\n",
		   sphere->center.x, sphere->center.y, sphere->center.z, 
		   sphere->r, sphere->colr.r, sphere->colr.g, sphere->colr.b);
	
	return sphere;
}


// Parse a plane
t_plane *parse_plane(t_parser *parser)
{
	t_plane *plane = malloc(sizeof(t_plane));

	if (!plane)
		return (NULL); // Handle allocation error
	plane->pop = parse_v3(parser);
	plane->normal = parse_v3(parser);
	plane->colr = parse_color(parser);
	return plane;
}

// Parse a cylinder
t_cylinder *parse_cylinder(t_parser *parser)
{
	t_cylinder *cylinder = malloc(sizeof(t_cylinder));

	if (!cylinder)
		return (NULL); // Handle allocation error
	cylinder->center = parse_v3(parser);
	cylinder->axis = parse_v3(parser);
	cylinder->radius = parse_number(parser->tokenizer);
	cylinder->height = parse_number(parser->tokenizer);
	cylinder->colr = parse_color(parser);
	return cylinder;
}

// Helper functions to parse numbers and colors

// Parse color tokens
// t_colr parse_color(t_parser *parser)
// {
//     t_colr color;
//     t_token *token;
//     // Parse r
//     token = tokenizer_next(parser->tokenizer);
//     if (!token || token->type != TOKEN_TYPE_NUMBER) {
//         // Handle error
//     }
//     color.r = (int)token->u_value.num;
//     token_free(token);
//     // Parse g
//     token = tokenizer_next(parser->tokenizer);
//     if (!token || token->type != TOKEN_TYPE_NUMBER) {
//         // Handle error
//     }
//     color.g = (int)token->u_value.num;
//     token_free(token);
//     // Parse b
//     token = tokenizer_next(parser->tokenizer);
//     if (!token || token->type != TOKEN_TYPE_NUMBER) {
//         // Handle error
//     }
//     color.b = (int)token->u_value.num;
//     token_free(token);
//     return color;
// }

t_colr parse_color(t_parser *parser)
{
	t_colr color = {255, 255, 255};  // Default white (more visible than black)
	t_token *token;
	
	// Get the color token (should be something like "255,0,0")
	token = tokenizer_next(parser->tokenizer);
	debug_token(token, "in parse_color");
	
	if (!token)
		return color;
	
	// Handle different token types
	if (token->type == TOKEN_TYPE_KEYWORD) {
		// Split the string by commas
		char **parts = ft_split(token->u_value.str, ',');
		if (parts && parts[0] && parts[1] && parts[2]) {
			// Parse the three components
			color.r = ft_atoi(parts[0]);
			color.g = ft_atoi(parts[1]);
			color.b = ft_atoi(parts[2]);
			
			// Clean up
			for (int i = 0; parts[i]; i++)
				free(parts[i]);
			free(parts);
		}
	} else if (token->type == TOKEN_TYPE_NUMBER) {
		// Single number might be brightness, not color
		// Keep default color
	}
	
	token_free(token);
	printf("Parsed color: (%d, %d, %d)\n", color.r, color.g, color.b);
	return color;
}



// Helper function to parse coordinates from a string like "-50.0,0,20"
// t_v3 parse_v3(t_parser *parser)
// {
//     t_v3 v3;
//     t_token *token;
//     // Parse x
//     token = tokenizer_next(parser->tokenizer);
//     if (!token || token->type != TOKEN_TYPE_NUMBER) {
//         // Handle error
//     }
//     v3.x = token->u_value.num;
//     token_free(token);
//     // Parse y
//     token = tokenizer_next(parser->tokenizer);
//     if (!token || token->type != TOKEN_TYPE_NUMBER) {
//         // Handle error
//     }
//     v3.y = token->u_value.num;
//     token_free(token);
//     // Parse z
//     token = tokenizer_next(parser->tokenizer);
//     if (!token || token->type != TOKEN_TYPE_NUMBER) {
//         // Handle error
//     }
//     v3.z = token->u_value.num;
//     token_free(token);
//     return (v3);
// }


t_v3 parse_v3(t_parser *parser)
{
	t_v3 v3 = {0, 0, 0};  // Default values
	t_token *token;
	
	// Get the coordinate token (should be something like "-50,0,20")
	token = tokenizer_next(parser->tokenizer);
	debug_token(token, "in parse_v3");
	
	if (!token || token->type != TOKEN_TYPE_KEYWORD)
		return v3;  // Return default values if parsing fails
	
	// Split the string by commas
	char **parts = ft_split(token->u_value.str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
	{
		// Cleanup and return defaults if split fails
		if (parts)
		{
			for (int i = 0; parts[i]; i++)
				free(parts[i]);
			free(parts);
		}
		token_free(token);
		return v3;
	}
	
	// Parse the three components
	v3.x = atof(parts[0]);  // Use ft_atof when implemented
	v3.y = atof(parts[1]);
	v3.z = atof(parts[2]);
	
	// Clean up
	for (int i = 0; parts[i]; i++)
		free(parts[i]);
	free(parts);
	token_free(token);
	
	printf("Parsed v3: (%f, %f, %f)\n", v3.x, v3.y, v3.z);
	return v3;
}


void token_free(t_token *token)
{
	if (token) {
		if (token->type == TOKEN_TYPE_KEYWORD ||
			token->type == TOKEN_TYPE_IDENTIFIER ||
			token->type == TOKEN_TYPE_SYMBOL) {
			free(token->u_value.str);
		}
		free(token);
	}
}
