/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_stuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:29:11 by fmaurer           #+#    #+#             */
/*   Updated: 2025/03/20 21:54:56 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "xpm/xpm.h"

// WARNING: the range for FOV is only (0, 180) meaning 0 and 180 not included!!!
// Explanation: 180deg would lead to a infinitely large vierwport width. 0 to 0.
// We need to check for that during map parsing!!!
void	init_cam(t_mrt mrt)
{
	t_camera	*cam;

	mrt.scene->cam = malloc(sizeof(t_camera));
	cam = mrt.scene->cam;
	// cam->pos = v3_new(0, 3, -3);
	// cam->orient = v3_new(0, -1, 1.5);
	cam->pos = v3_new(-5, 0, -3);
	cam->orient = v3_new(1, 0, 1);
	// cam->pos = v3_new(0, 0, -1);
	// cam->orient = v3_new(0, 0, 1);
	cam->fov = M_PI_4;
	cam->rot = get_rotmtrx(v3_get_norm(cam->orient));
	cam->view_width = 2 * tan(cam->fov/2);
	cam->cvr = cam->view_width / CANVAS_WIDTH;
	printf("cam->viewport_width = %lf\n", cam->view_width);
}

void	init_objs(t_mrt mrt)
{
	t_objlst	**objs;

	mrt.scene->objects = NULL;
	objs = &mrt.scene->objects;
	// t_sphere	*sphere1 = malloc(sizeof(t_sphere));
	// *sphere1 = (t_sphere){v3_new(0, 0, 10), 2, 2 * 2, (t_colr){255, 0, 0}};
	// t_sphere	*sphere2 = malloc(sizeof(t_sphere));
	// *sphere2 = (t_sphere){v3_new(4, 0, 14), 2, 2 * 2, (t_colr){0, 255, 0}};
	// t_sphere	*sphere3 = malloc(sizeof(t_sphere));
	// *sphere3 = (t_sphere){v3_new(-4, 0, 14), 1.5, 1.5 * 1.5, (t_colr){0, 0, 142}};

	t_sphere	*sphere1 = malloc(sizeof(t_sphere));
	*sphere1 = (t_sphere){v3_new(0, 0, 10), 2, 2 * 2, (t_colr){255, 0, 0}};
	t_sphere	*sphere2 = malloc(sizeof(t_sphere));
	*sphere2 = (t_sphere){v3_new(0, 0, 4), 1, 1, (t_colr){0, 255, 0}};
	// t_sphere	*sphere3 = malloc(sizeof(t_sphere));
	// *sphere3 = (t_sphere){v3_new(-4, 0, 14), 1.5, 1.5 * 1.5, (t_colr){0, 0, 142}};

	// t_sphere	*sphere4 = malloc(sizeof(t_sphere));
	// *sphere4 = (t_sphere){v3_new(-12, 0, 9), 1.5, 1.5 * 1.5, (t_colr){42, 42, 142}};
	// t_sphere	*sphere5 = malloc(sizeof(t_sphere));
	// *sphere5 = (t_sphere){v3_new(0, 12, 9), 1.5, 1.5 * 1.5, (t_colr){42, 42, 142}};
	// t_sphere	*sphere6 = malloc(sizeof(t_sphere));
	// *sphere6 = (t_sphere){v3_new(-6, 0, 9), 1.5, 1.5 * 1.5, (t_colr){42, 42, 142}};
	objlst_add_back(objs, objlst_new(SPHERE, sphere1));
	objlst_add_back(objs, objlst_new(SPHERE, sphere2));
	// objlst_add_back(objs, objlst_new(SPHERE, sphere3));
	// objlst_add_back(objs, objlst_new(SPHERE, sphere4));
	// objlst_add_back(objs, objlst_new(SPHERE, sphere5));
	// objlst_add_back(objs, objlst_new(SPHERE, sphere6));
}

void	init_lights(t_mrt mrt)
{
	t_objlst	**objs;

	mrt.scene->alight = malloc(sizeof(t_amb_light));
	mrt.scene->alight->bright = 0.3;
	mrt.scene->alight->colr = (t_colr){255, 255, 255};
	// mrt.scene->alight->colr = (t_colr){255, 100, 100};

	objs = &mrt.scene->objects;

	t_light	*light1 = malloc(sizeof(t_light));
	light1->bright = 1.0;
	// light1->colr = (t_colr){255, 0, 0};
	light1->colr = (t_colr){255, 255, 255};
	light1->pos = (t_v3){0, 0, -6};
	objlst_add_back(objs, objlst_new(LIGHT, light1));

	// t_light	*light1 = malloc(sizeof(t_light));
	// light1->bright = 1.0;
	// // light1->colr = (t_colr){255, 0, 0};
	// light1->colr = (t_colr){255, 255, 255};
	// light1->pos = (t_v3){0, 2.9, 10};
	// objlst_add_back(objs, objlst_new(LIGHT, light1));

	// t_light	*light2 = malloc(sizeof(t_light));
	// light2->bright = 0.9;
	// light2->colr = (t_colr){0, 0, 255};
	// light2->pos = (t_v3){0, -2.1, 8};
	// objlst_add_back(objs, objlst_new(LIGHT, light2));

	// t_light	*light2 = malloc(sizeof(t_light));
	// light2->bright = 0.5;
	// // light2->colr = (t_colr){0, 0, 255};
	// light2->colr = (t_colr){255, 255, 100};
	// light2->pos = (t_v3){-5, 0, 3};
	// objlst_add_back(objs, objlst_new(LIGHT, light2));
}

void	init_scene(t_mrt mrt)
{
	init_objs(mrt);
	init_cam(mrt);
	init_lights(mrt);
	mrt.scene->subsample = 1;
}

int	color_map_2(t_mrt mrt, unsigned char *data,int bpp,int sl,int w,int h, int type)
{
  int	x;
  int	y;
  int	opp;
  int	dec;
  int	color;
  int	color2;
  unsigned char *ptr;

  opp = bpp/8;
  printf("(opp : %d) ",opp);
  y = h;
  while (y--)
  {
	  ptr = data+y*sl;
	  x = w;
	  while (x--)
	  {
		  if (type==2)
			  color = (y*255)/w+((((w-x)*255)/w)<<16)
				  +(((y*255)/h)<<8);
		  else
			  color = (x*255)/w+((((w-x)*255)/w)<<16)+(((y*255)/h)<<8);
		  color2 = mlx_get_color_value(mrt.mlx, color);
		  dec = opp;
		  while (dec--)
			  *(ptr+x*opp+dec) = ((unsigned char *)(&color2))[dec];
	  }
  }
  return(0);
}

int	my_colormap(t_mrt mrt, unsigned char *data, int bpp, int sl, int w, int h,
		int type)
{
  int	x;
  int	y;
  int	opp;
  int	dec;
  int	color;
  int	color2;
  unsigned char *ptr;

  opp = bpp/8; // with 32 bits opp == 4
  y = h;
  while (y--)
  {
	  ptr = &data[y * sl];
	  x = w;
	  while (x--)
	  {
		  if (type==2)
			  color = (y * 255)/w + ((((w-x)*255)/w)<<16) + (((y*255)/h)<<8);
		  else
			  color = (x*255)/w+((((w-x)*255)/w)<<16)+(((y*255)/h)<<8);
		  color2 = mlx_get_color_value(mrt.mlx, color);
		  dec = opp;
		  while (dec--)
			  *(ptr+x*opp+dec) = ((unsigned char *)(&color2))[dec];
	  }
  }
  return(0);
}
int	draw_cross(t_mrt mrt, unsigned char *data, int bpp, int sl, int w, int h)

{
  int	x;
  int	y;
  int	opp;
  int	dec;
  int	color;
  int	colr2;
  unsigned char *ptr;

  opp = bpp/8; // with 32 bits opp == 4
  y = h;
  while (y--)
  {
	  ptr = &data[y * sl];
	  x = w;
	  while (x--)
	  {
		  color = mlx_get_color_value(mrt.mlx, rgb_to_int("000000"));
		  colr2 = mlx_get_color_value(mrt.mlx, rgb_to_int("aa00ff"));
		  dec = opp;
		  while (dec--)
		  {
			  if (x == y)
				  *(ptr+x*opp+dec) = ((unsigned char *)(&colr2))[dec];
			  else
				  *(ptr+x*opp+dec) = ((unsigned char *)(&color))[dec];
		  }
	  }
  }
  return(0);
}

void	do_stuff_xpm_test(t_mrt mrt)
{

	void *pic = mlx_new_image(mrt.mlx, CANVAS_WIDTH, WINY);
	int bpp, sl, endian;
	char *data = mlx_get_data_addr(pic, &bpp, &sl, &endian);
	my_colormap(mrt, (unsigned char *)data, bpp, sl, CANVAS_WIDTH, WINY, 2);
	mlx_put_image_to_window(mrt.mlx, mrt.win, pic, SIDEBAR_AREA_X, 0);
	printf("\nbpp = %d\n", bpp);
	printf("endian = %d\n", endian);

	int	im_width;
	int	im_height;
	void *xpm = mlx_xpm_file_to_image(mrt.mlx, "./snowflake.xpm", &im_width, &im_height);
	mlx_put_image_to_window(mrt.mlx, mrt.win, xpm, 100, 100);

	void *pic1 = mlx_new_image(mrt.mlx, CANVAS_WIDTH, WINY);
	int bpp1, sl1, endian1;
	char *data1 = mlx_get_data_addr(pic1, &bpp1, &sl1, &endian1);
	draw_cross(mrt, (unsigned char *)data1, bpp1, sl1, CANVAS_WIDTH, WINY);
	// put_pixel_xpm(mrt, (unsigned char *)data1, bpp1, sl1, 0, 0, (t_colr){0, 0, 255});
	// put_pixel_xpm(mrt, (unsigned char *)data1, bpp1, sl1, 0, 1, (t_colr){0, 0, 255});
	// put_pixel_xpm(mrt, (unsigned char *)data1, bpp1, sl1, 0, -1, (t_colr){0, 0, 255});
	// put_pixel_xpm(mrt, (unsigned char *)data1, bpp1, sl1, 1, 0, (t_colr){0, 0, 255});
	// put_pixel_xpm(mrt, (unsigned char *)data1, bpp1, sl1, 1, 1, (t_colr){0, 0, 255});
	// put_pixel_xpm(mrt, (unsigned char *)data1, bpp1, sl1, 1, -1, (t_colr){0, 0, 255});
	// put_pixel_xpm(mrt, (unsigned char *)data1, bpp1, sl1, -1, 0, (t_colr){0, 0, 255});
	// put_pixel_xpm(mrt, (unsigned char *)data1, bpp1, sl1, -1, 1, (t_colr){0, 0, 255});
	// put_pixel_xpm(mrt, (unsigned char *)data1, bpp1, sl1, -1, -1, (t_colr){0, 0, 255});
	mlx_put_image_to_window(mrt.mlx, mrt.win, pic1, SIDEBAR_AREA_X, 0);
}

void	do_stuff(t_mrt mrt)
{

	init_scene(mrt);
	show_sidebar(mrt);
	print_scene(*mrt.scene);

	raytrace(mrt);

	// xc = raytrace_xpm(mrt);
	// t_xpm_canvas	*xc;
	// mlx_put_image_to_window(mrt.mlx, mrt.win, xc->img, SIDEBAR_AREA_X, 0);
}

