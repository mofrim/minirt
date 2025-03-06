/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:46:04 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/06 09:52:58 by fmaurer          ###   ########.fr       */
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
# define WINX 1400
# define WINY 1000

# define FONT "-misc-fixed-*-*-*-*-30-*-*-*-*-*-*-*"
// # define FONT "-*-*-*-*-*-*-*-*-*-*-*-*-*-*"
// # define FONT "-misc-fixed-bold-r-normal--18-120-100-100-c-90-iso8859-1"
// # define FONT "-misc-fixed-medium-r-normal--20-200-75-75-c-100-iso8859-1"


/********** Structs. **********/

/* A first idea of a struct for the camera. */
typedef struct {
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

/********** Utilities. **********/

int		rgb_to_int(char *rgbstr);
void	int_to_rgb(int rgb_arr[3], int rgb_num);

#endif
