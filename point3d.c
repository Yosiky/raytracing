#include "point3d.h"

char	ee_set_point(t_point3d *point, float x, float y, float z)
{
	char	flag;

	flag = 0;
	if (point == (void *)0)
	{
		point = (t_point3d *)malloc(sizeof(t_point3d));
		flag = 1;
	}
	point->x = x;
	point->y = y;
	point->z = z;
	return (flag);
}

char	ee_point_minus(t_point3d *res, t_point3d *a, t_point3d *b)
{
	char	flag;

	flag = 0;
	if (res == (void *)0)
	{
		res = (t_point3d *)malloc(sizeof(t_point3d));
		flag = 1;
	}
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	res->z = a->z - b->z;
	return (flag);
}

char	ee_point_div(t_point3d *res, float val)
{
	char	flag;

	flag = 0;
	if (val == 0)
		return (-1);
	if (res == (void *)0)
	{
		res = (t_point3d *)malloc(sizeof(t_point3d));
		flag = 1;
	}
	res->x /= val;
	res->y /= val;
	res->z /= val;
	return (flag);
}

float	ee_point_dot(t_point3d *a, t_point3d *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

void	ee_point_norm(t_point3d *obj)
{
	float	len;

	len = ee_point_len(obj);
	ee_point_div(obj, len);
}

float	ee_point_len(t_point3d *obj)
{
	return (sqrt(obj->x * obj->x + obj->y * obj->y + obj->z * obj->z));
}

void	ee_point_print(t_point3d *obj)
{
	printf ("point: {%f, %f, %f}", obj->x, obj->y, obj->z);
}
