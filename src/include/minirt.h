/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:46:04 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/08 14:41:10 by fmaurer          ###   ########.fr       */
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

/* for uint8_t, ... */
# include <stdint.h>

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"

/********** LinalAlg headers. **********/
# include "vec3.h"
# include "v3.h"
# include "ray.h"

/********** Consts. **********/

# include "constants.h"

/********** The Objects. **********/

# include "objects.h"

/********** Structs. **********/

/* In principle a 2d vector... */
typedef struct s_v2
{
	double	x1;
	double	x2;
}	t_v2;


/* The scene master struct. */
typedef struct s_scene
{
	t_camera	*cam;
	t_amb_light	alight;
	t_objlst	*objects;
}	t_scene;


/* A pixel on our screen. */
typedef struct s_pxl
{
	int	x;
	int	y;
}	t_pxl;

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
t_mrt	*init_mrt(t_scene *scene);
int		close_btn_handler(t_mrt *mrt);
int		kbd_input_handler(int key, t_mrt *mrt);
void	show_sidebar(t_mrt mrt);
void	raytrace(t_mrt mrt);

/********** Utilities. **********/

int		rgb_to_int(char *rgbstr);
void	int_to_rgb(int rgb_arr[3], int rgb_num);
void	put_pixel_win(t_mrt	mrt, t_pxl pos, char *colr);
void	put_pixel_canvas(t_mrt	mrt, t_pxl pos, char *colr);
void	put_pixel_canvas_rt(t_mrt mrt, t_pxl pos, t_colr pxlcolr);
void	put_string(t_mrt mrt, t_pxl pos, char *colr, char *txt);
void	print_scene(t_scene scene);
int		tcolr_to_int(t_colr colr);
t_colr	int_to_tcolr(int int_colr);

/********** Objects. **********/

void	draw_disk(t_pxl p, int radius, char *colr, t_mrt mrt);

/********** Do stuff. **********/

void	do_stuff(t_mrt mrt);

#endif
