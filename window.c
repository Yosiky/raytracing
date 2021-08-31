#include "window.h"

t_window	*ee_create_window(int w, int h, Uint32 color)
{
	t_window	*res;

	res = (t_window *)malloc(sizeof(t_window));
	if (!res)
		return (res);
	res->window = SDL_CreateWindow("Raytracing",
									SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									w, h, 0);
	res->width = w;
	res->heigth = h;
	res->background = color;
	return (res);
}

void	ee_delete_window(t_window *window)
{
	SDL_DestroyWindow(window->window);
	free(window);
}

void	ee_window_print(t_window *obj)
{
	printf("Window:\nwidth = %d, heigth = %d\ncolor: {%d, %d, %d}\n\n", 
	obj->width, obj->heigth, 0xff & (obj->background), 
	0xff & (obj->background >> 8), 0xff & (obj->background >> 16));
}
