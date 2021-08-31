#include <stdio.h>
#include <SDL2/SDL.h>

void	ee_print_color(Uint32 color)
{
	printf("color: {%d, %d, %d}",  0xff & (color),
                                          0xff & (color >> 8),
                                          0xff & (color >> 16));
}
