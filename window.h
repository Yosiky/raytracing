#ifndef WINDOW_H
# define WINDOW_H

# include <SDL2/SDL.h>
# include <stdlib.h>

typedef struct s_window
{
	SDL_Window		*window;
	int				width;
	int				heigth;
	Uint32			background;
}	t_window;

t_window	*ee_create_window(int w, int h, Uint32 color);
void		ee_window_print(t_window *obj);
void		ee_delete_window(t_window *window);

#endif
