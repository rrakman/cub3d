/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:00:21 by rrakman           #+#    #+#             */
/*   Updated: 2024/06/03 21:31:04 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(t_game *game, int flag)
{
	normalize_angle(&game->ray->angle);
	if (flag == 0)
	{
		if (game->ray->angle > M_PI / 2 && game->ray->angle < 3 * (M_PI / 2))
			return (WHITE);
		else
			return (WHITE);
	}
	else
	{
		if (game->ray->angle > 0 && game->ray->angle < M_PI)
			return (DARK_GREEN);
		else
			return (DARK_GREEN);
	}
}

void	draw_wall(t_game *game, int ray, int t_pix, int b_pix)
{
	int	color;

	color = get_color(game, game->ray->flag);
	while (t_pix < b_pix)
		mlx_put_pixel(game->cub, ray, t_pix++, color);
}

void	draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix)
{
	int	i;

	i = b_pix;
	while (i < 800)
		mlx_put_pixel(game->cub, ray, i++, ft_pixel(game->data->floor_rgb[0],
				game->data->floor_rgb[1], game->data->floor_rgb[2], 255));
	i = 0;
	while (i < t_pix)
		mlx_put_pixel(game->cub, ray, i++, ft_pixel(game->data->ceiling_rgb[0],
				game->data->ceiling_rgb[1], game->data->ceiling_rgb[2], 255));
}

void	render_walls(t_game *game, float distance, int ray)
{
	float	wall_h;
	float	b_pix;
	float	t_pix;
	float	angle;

	angle = game->ray->angle - game->angle;
	normalize_angle(&angle);
	distance *= cos(angle);
	wall_h = (game->tale_size / distance) * ((S_W / 2) / tan(game->fov_rd / 2));
	b_pix = (S_W / 2) + (wall_h / 2);
	t_pix = (S_W / 2) - (wall_h / 2);
	if (b_pix > S_W)
		b_pix = S_W;
	if (t_pix < 0)
		t_pix = 0;
	draw_wall(game, ray, t_pix, b_pix);
	draw_floor_ceiling(game, ray, t_pix, b_pix);
}

void	cast_rays(t_game *game)
{
	int		ray;
	float	horiz_i;
	float	vert_i;
	float	chose;

	normalize_angle(&game->angle);
	game->ray->angle = game->angle - game->fov_rd / 2;
	ray = 0;
	while (ray < 800)
	{
		normalize_angle(&game->ray->angle);
		game->ray->flag = 0;
		horiz_i = horizontal_intersection(game);
		vert_i = vertical_intersection(game);
		if (vert_i <= horiz_i)
			chose = vert_i;
		else
		{
			chose = horiz_i;
			game->ray->flag = 1;
		}
		render_walls(game, chose, ray);
		ray++;
		game->ray->angle += game->increment;
	}
}
