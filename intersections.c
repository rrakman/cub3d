/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:05:42 by rrakman           #+#    #+#             */
/*   Updated: 2024/06/03 16:11:34 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_hit(t_game *game, float x, float y)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = (int)(x / game->tale_size);
	y_m = (int)(y / game->tale_size);
	if ((y_m >= game->map_height || x_m >= game->map_width))
		return (0);
	if (game->data->map[y_m] && x_m <= (int)strlen(game->data->map[y_m]))
		if (game->data->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

int	inter_check(t_game *game, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (game->ray->angle > 0 && game->ray->angle < M_PI)
		{
			*inter += game->tale_size;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(game->ray->angle > M_PI / 2 && game->ray->angle < 3 * M_PI / 2)) 
		{
			*inter += game->tale_size;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	check_angle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

float	horizontal_intersection(t_game *game)
{
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = game->tale_size;
	x_step = game->tale_size / tan(game->ray->angle);
	game->ray->y = floor(game->player_yp / game->tale_size) * game->tale_size;
	pixel = inter_check(game, &game->ray->y, &y_step, 1);
	game->ray->x = game->player_xp + \
		(game->ray->y - game->player_yp) / tan(game->ray->angle);
	if ((check_angle(game->ray->angle, 'y') && x_step > 0) \
		|| (!check_angle(game->ray->angle, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(game, game->ray->x, game->ray->y - pixel))
	{
		game->ray->x += x_step;
		game->ray->y += y_step;
	}
	return (sqrt(pow(game->ray->x - game->player_xp, 2) \
		+ pow(game->ray->y - game->player_yp, 2)));
}

float	vertical_intersection(t_game *game)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = game->tale_size; 
	y_step = game->tale_size * tan(game->ray->angle);
	v_x = floor(game->player_xp / game->tale_size) * game->tale_size;
	pixel = inter_check(game, &v_x, &x_step, 0);
	v_y = game->player_yp + (v_x - game->player_xp) * tan(game->ray->angle);
	if ((check_angle(game->ray->angle, 'x') && y_step < 0) \
		|| (!check_angle(game->ray->angle, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(game, v_x - pixel, v_y))
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - game->player_xp, 2) \
		+ pow(v_y - game->player_yp, 2)));
}
