#include "sphere.h"

t_sphere	*ee_create_sphere(t_point3d *center, int r, Uint32 col)
{
	t_sphere	*res;

	res = (t_sphere *)malloc(sizeof(t_sphere));
	if (!res)
		return ((void *)0);
	ee_set_point(&res->center, center->x, center->y, center->z);
	res->radius = r;
	res->color = col;
	return (res);
}

void	ee_sphere_print(t_sphere *obj)
{
	printf("Sphere:\n");
	ee_point_print(&obj->center);
	printf(", color: {%d, %d, %d}\n\n",  0xff & (obj->color),
										  0xff & (obj->color >> 8),
										  0xff & (obj->color >> 16));
}
