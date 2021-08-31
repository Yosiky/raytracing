#ifndef POINT3D_H
# define POINT3D_H

# include <SDL2/SDL.h>

typedef struct s_point3d
{
	float	x;
	float	y;
	float	z;
}	t_point3d;

char	ee_set_point(t_point3d *point, float x, float y, float z);
char	ee_point_minus(t_point3d *res, t_point3d *a, t_point3d *b);
char	ee_point_div(t_point3d *res, float val);
float	ee_point_dot(t_point3d *a, t_point3d *b);
float	ee_point_len(t_point3d *obj);
void	ee_point_print(t_point3d *obj);
void	ee_point_norm(t_point3d *obj);

#endif
