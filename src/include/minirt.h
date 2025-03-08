/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:46:04 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/07 21:10:05 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* all the math... */
# include <math.h>

/* free, malloc */
# include <stdlib.h>

/* read, close */
# include <unistd.h>

/* write */
# include <fcntl.h>

/* perror */
# include <stdio.h>

/* strerror */
# include <string.h>

/* errno */
# include <errno.h>

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"

/********** LinalAlg headers. **********/
# include "vec3.h"
# include "v3.h"
# include "ray.h"

/********** Consts. **********/

# include "constants.h"

/********** Structs. **********/

/* A pixel on our screen. */
typedef struct s_pxl
{
	int	x;
	int	y;
}	t_pxl;

/* A first idea of a struct for the camera. */
typedef struct s_camera{
    t_vec3	position;
    t_vec3	look_at;
    t_vec3	up;
    double	fov;
    double	aspect_ratio;
}	t_camera;

typedef struct s_scene
{
	t_camera	*cam;
	// objects linked list
	// lights linked list
	// etc...
}	t_scene;

/* The MiniRT master-struct holding all nesessary data and pointers to struct
 * needed throughout the program. */
typedef struct s_mrt
{
	t_xvar		*mlx;
	t_win_list	*win;
	t_scene		*scene;
}	t_mrt;

/********** General functions. **********/

t_scene	*parse_scene(char *scene_file);
t_mrt	*init_mrt(void);
int		close_btn_handler(t_mrt *mrt);
int		kbd_input_handler(int key, t_mrt *mrt);
void show_sidebar(t_mrt mrt);

/********** Utilities. **********/

int		rgb_to_int(char *rgbstr);
void	int_to_rgb(int rgb_arr[3], int rgb_num);
void	put_pixel_win(t_mrt	mrt, t_pxl pos, char *colr);
void	put_pixel_canvas(t_mrt	mrt, t_pxl pos, char *colr);
void	put_string(t_mrt mrt, t_pxl pos, char *colr, char *txt);

/********** Objects. **********/

void	draw_disk(t_pxl p, int radius, char *colr, t_mrt mrt);


#endif
