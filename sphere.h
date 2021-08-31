#ifndef SPHERE_H
# define SPHERE_H

# include <stdio.h>
# include <SDL2/SDL.h>
# include "point3d.h"

typedef struct s_sphere
{
	t_point3d	center;
	float		radius;
	Uint32		color;
}	t_sphere;

t_sphere	*ee_create_sphere(t_point3d *center, int r, Uint32 col);
void		ee_sphere_print(t_sphere *obj);

#endif
