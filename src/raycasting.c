/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:00:21 by rrakman           #+#    #+#             */
/*   Updated: 2024/06/09 17:50:43 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_offset_x(t_game *game, float *offset_x)
{
	if (game->ray->flag == 1)
		*offset_x = fmod((int)(game->ray)->y, game->tale_size);
	else
		*offset_x = fmod((int)(game->ray)->x, game->tale_size);
}

void	draw_wall(t_game *game, int ray, int t_pix, int b_pix)
{
	int				color;
	mlx_texture_t	*texture;
	float			offset_x;
	int				distance_from_top;
	float			offset_y;

	texture = get_right_texture(game);
	t_pix = fmax(0, (S_W / 2) - (game->wall_h / 2));
	b_pix = fmin(S_W, (S_W / 2) + (game->wall_h / 2));
	calculate_offset_x(game, &offset_x);
	while (t_pix < b_pix)
	{
		distance_from_top = t_pix - ((int)((S_W / 2) \
			- ((int)game->wall_h / 2)));
		offset_y = distance_from_top * ((float)texture->height
				/ (int)game->wall_h);
		if (offset_y >= texture->height)
			offset_y = texture->height;
		if (offset_y < 0)
			offset_y = 0;
		color = get_color_at(offset_x, offset_y, texture);
		mlx_put_pixel(game->cub, ray, t_pix, color);
		t_pix++;
	}
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

void	render_walls(t_game *game, double distance, int ray)
{
	float	b_pix;
	float	t_pix;
	float	angle;

	angle = game->ray->angle - game->angle;
	normalize_angle(&angle);
	distance *= cos(angle);
	game->wall_h = (game->tale_size / distance) * ((S_W / 2) / tan(game->fov_rd
				/ 2));
	b_pix = fmin(S_W, (S_W / 2) + (game->wall_h / 2));
	t_pix = fmax(0, (S_W / 2) - (game->wall_h / 2));
	draw_wall(game, ray, t_pix, b_pix);
	draw_floor_ceiling(game, ray, t_pix, b_pix);
}

void	cast_rays(t_game *game)
{
	int		ray;
	double	horiz_i;
	double	vert_i;
	double	chose;

	normalize_angle(&game->angle);
	game->ray->angle = game->angle - game->fov_rd / 2;
	ray = 0;
	while (ray < S_W)
	{
		normalize_angle(&game->ray->angle);
		game->ray->flag = 0;
		calcul_intersections(game, &horiz_i, &vert_i, &chose);
		render_walls(game, chose, ray);
		ray++;
		game->ray->angle += game->increment;
	}
}
