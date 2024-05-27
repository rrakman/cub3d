#include"cub3d.h"

float degree_to_radian(float degree)
{
	return (degree * (M_PI / 180));
}

void normalize_angle(float *angle)
{
	if (*angle < 0)
		*angle += 2 * M_PI;
	if (*angle > 2 * M_PI)
		*angle -= 2 * M_PI;
}