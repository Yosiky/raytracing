#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "window.h"
#include "point3d.h"
#include "sphere.h"
#include <math.h>

#define INF	2147483647

float		eps = 0.0000001;
int			Vh = 1; // set in 1x1x1
int			Vw = 1;
int			Vd = 1;
int			Ch = 600; //разрешение
int			Cw = 600;
int			count_figure;
t_sphere	**spheres;
t_window	*window;

void	putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void	ee_print_color(Uint32 color);

void	canvastoviewport(t_point3d *d, float x, float y)
{
	ee_set_point(d, x * Vw / Cw, y * Vh / Ch, Vd);
}

void	intersectraysphere(t_point3d *o, t_point3d *d, t_sphere *s, float res[2])
{
	t_point3d	oc;
	float		r;
	float		k1;
	float		k2;
	float		k3;
	float		disc;

	res[0] = INF;
	res[1] = INF;
	ee_point_minus(&oc, o, &(s->center));
	r = s->radius;
	k1 = ee_point_dot(d, d);
	k2 = 2 * ee_point_dot(&oc, d);
	k3 = ee_point_dot(&oc, &oc) - r * r;
	disc = k2 * k2 - 4 * k1 * k3;
	if (disc < 0)
		return ;
	res[0] = (-k2 - sqrt(disc)) / (2 * k1);
	res[1] = (-k2 + sqrt(disc)) / (2 * k1);
}

Uint32	traceray(t_point3d	*o, t_point3d *d, float minimal, float maximal)
{
	float	len;
	float	res[2];
	Uint32	color;

	len	= INF;
	color = window->background;
	for (int i = 0; i < count_figure; i++)
	{
		intersectraysphere(o, d, spheres[i], res);
		for (int j = 0; j < 2; j++)
		{
			if (minimal <= res[j] && res[j] <= maximal && res[j] < len)
			{
				len = res[j];
				color = spheres[i]->color;
			}
		}
	}
	return (color);
}

void	setcanvas(SDL_Surface *surface)
{
	t_point3d	o;
	t_point3d	d;
	Uint32		color;

	ee_set_point(&o, 0, 0, 0);
	for	(int i = -Cw / 2; i <= Cw / 2; i++)
	{
		//printf("Start:\n");
		for (int j = -Ch / 2; j <= Ch / 2; j++)
		{
			canvastoviewport(&d, i, j);
			color = traceray(&o, &d, 1, INF);
			//printf("\ti = %d, j = %d\n\t\t", i, j);
			//ee_print_color(color);
			//printf("\n");
			putpixel(surface, i + Cw / 2, Ch / 2 - j, color);
		}
		//print1f("End\n\n");
	}
}

void	start(t_window *window)
{
	SDL_Event	e;

	setcanvas(SDL_GetWindowSurface(window->window));	
	SDL_UpdateWindowSurface(window->window);
	while (1)
	{
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
			SDL_Log("Program quit after %i ticks", e.quit.timestamp);
			break;
		}
	}
}

void	delete(void	**figures, int n) {
	for (int i = 0; i < n; i++)
		free(figures[i]);
	free(figures);
}

int	main(int argc, char **argv)
{
	Uint32	color;
	t_point3d	point;
	
	color = 0;
	color |= 127;
	color |= 127 << 8;
	color |= 127 << 16;
	count_figure = 3;
	spheres = (t_sphere **)malloc(sizeof(t_sphere *) * count_figure);
	ee_set_point(&point, 0, -1, 3);
	spheres[0] = ee_create_sphere(&point, 1, 255<<16);
	ee_set_point(&point, 2, 0, 4);
	spheres[1] = ee_create_sphere(&point, 1, 255);
	ee_set_point(&point, -2, 0, 4);
	spheres[2] = ee_create_sphere(&point, 1, 255<<8);
	ee_sphere_print(spheres[0]);
	ee_sphere_print(spheres[1]);

	if (argc && argv)
		write(1, "Start program\n", 14);
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("Error in SDL_Init\n");
		return (0);
	}
	window = ee_create_window(Cw, Ch, color);	
    if (!window->window)
	{
		printf("Failed to create window\n");
		return (0);
	}	
	ee_window_print(window);
	start(window);
	//SDL_Delay(5000);
	printf("End programm\n");
	ee_delete_window(window);
	delete((void **)spheres, count_figure);
	return (0);
}
