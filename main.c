#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "window.h"
#include "point3d.h"
#include "sphere.h"
#include <math.h>

#define INF	2147483647

int			heigth_window = 480; //размер окна
int			width_window = 640;
int			Ch = 1080; //разрешение
int			Cw = 1920;
int			count_figure;
t_sphere	**spheres;
t_window	*window;

void	putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void	ee_print_color(Uint32 color);

void	canvastoviewport(t_point3d *point, float x, float y) 
{
	ee_set_point(point, x / width_window * Cw, y / heigth_window * Ch, 1);
}

void	itersectraysphere(t_point3d *o, t_point3d *d, t_sphere *figure, float *res)
{
	float		k1;
	float		k2;
	float		k3;
	float		discriminant;
	t_point3d	oc;

	ee_point_minus(&oc, o, &figure->center);
	printf("\noc = ");
	ee_point_print(&oc);
	printf("\nd = ");
	ee_point_print(d);
	//ee_point_norm(&oc);
	printf("\nnoc = ");
	ee_point_print(&oc);
	*res = INF;
	k1 = ee_point_dot(d, d);
	k2 = 2 * ee_point_dot(&oc, d);
	k3 = ee_point_dot(&oc, &oc) - figure->radius * figure->radius;
	discriminant = k2 * k2 - 4 * k1 * k3;
	printf("%f %f %f dis = %f\n", k1, k2, k3, discriminant);
	if (discriminant >= 0)
	{
		if (k2 >= 0)
			*res = (-k2 + sqrt(discriminant)) / (2 * k1);
		else
			*res = (-k2 - sqrt(discriminant)) / (2 * k1);
	}
	printf("end iterspheres\n");
}

Uint32	traceray(t_point3d *o, t_point3d *d, float minimal, float maximal)
{
	t_sphere	*iter;
	float		len;
	float		res;

	len = maximal;
	iter = (void *)0;
	printf("figures:\n");
	for (int i = 0; i < count_figure; i++)
	{
		itersectraysphere(o, d, spheres[i], &res);
		if (minimal <= res && res <= maximal && res < len)
		{
			len = res;
			iter = spheres[i];
		}	
	}	
	if (iter == (void *)0)
		return (window->background);
	printf("end figures\n");
	return (iter->color);
}

void	setcanvas(t_window *window)
{
	SDL_Surface	*surface;
	t_point3d	d;
	t_point3d	o;	
	Uint32		color;
	
	ee_set_point(&o, 0, 0, 0);
	surface = SDL_GetWindowSurface(window->window);
	printf("Start to round\n");
	for (int i = -window->width / 2; i <= window->width / 2; i++)
	{
		for (int j = -window->heigth / 2; j <= window->heigth / 2; j++)
		{
			printf("\ti = %d, j = %d\n", i, j);
			canvastoviewport(&d, i, j);
			color = traceray(&o, &d, 1, INF);
			ee_print_color(color);
			printf("\n\n");
			putpixel(surface, i + window->width / 2, j + window->heigth / 2, color);
		}
	} 
	printf("End rount\n");
}

void	start(t_window *window)
{
	while (1)
	{
		setcanvas(window);	
		SDL_UpdateWindowSurface(window->window);
		break;
	}
}

void	delete(void	**figures, int n)
{
	for (int i = 0; i < n; i++)
		free(figures[i]);
	free(figures);
}

int	main(int argc, char **argv)
{
	Uint32	color;
	
	color = 0;
	color |= 127;
	color |= 127 << 8;
	color |= 127 << 16;
	if (argc && argv)
		write(1, "Start program\n", 14);
	SDL_Surface	*window_surface;

	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("Error in SDL_Init\n");
		return (0);
	}
	window = ee_create_window(width_window, heigth_window, color);	
    if (!window->window)
	{
		printf("Failed to create window\n");
		return (0);
	}	
	window_surface = SDL_GetWindowSurface(window->window);
	if (!window_surface)
	{
		printf("Failed to get the surface from the window\n");
		return (0);
	}
	ee_window_print(window);
	t_point3d	point;
	count_figure = 1;
	spheres = (t_sphere **)malloc(sizeof(t_sphere *) * count_figure);
	ee_set_point(&point, 0, -1, 3);
	spheres[0] = ee_create_sphere(&point, 1, 255<<16);
	//ee_set_point(&point, 10, 10, 10);
	//spheres[1] = ee_create_sphere(&point, 2, 255<<8);
	ee_sphere_print(spheres[0]);
	//ee_sphere_print(spheres[1]);
	start(window);
	SDL_Delay(5000);
	ee_delete_window(window);
	printf("End programm\n");
	delete((void **)spheres, count_figure);
	return (0);
}
