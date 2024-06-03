/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:05:18 by rrakman           #+#    #+#             */
/*   Updated: 2024/06/03 17:12:39 by rrakman          ###   ########.fr       */
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
	int		i;

	i = b_pix;
	while (i < 800)
		mlx_put_pixel(game->cub, ray, i++, GRAY);
	i = 0;
	while (i < t_pix)
		mlx_put_pixel(game->cub, ray, i++, CYAN);
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

void	cast_rays(t_game * game)
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

void fill_map(t_game *game, t_map *data)
{
	game->map = data->map;
	game->player_x = data->player_x;
	game->player_y = data->player_y;
	game->map_height = len2d(game->data->map);
	game->map_width = biggestline(game->data->map);
	game->tale_size = 32;
	game->player_xp = (game->player_x * game->tale_size) + (game->tale_size / 2);
	game->player_yp = (game->player_y * game->tale_size) + (game->tale_size / 2);
	game->pssh = game->tale_size / 12;
	define_angle(game, data->player_dir);
	game->fov_rd = FOV * M_PI / 180;
	game->ray = malloc(sizeof(t_ray));
	game->increment = (game->fov_rd / 800);
}

int	main(int ac, char **av)
{
	t_map	data;
	t_game	*game;

	if (ac == 2)
	{
		first_check(av, &data);
		map_check(&data);
		game = malloc(sizeof(t_game));
		game->data = &data;
		fill_map(game, &data);
		game->mlx = mlx_init(800, 800, "CUB3D", 0);
		if (!game->mlx)
			ft_error();
		game->minimap = mlx_new_image(game->mlx, \
			game->map_width * game->tale_size, \
				game->map_height * game->tale_size);
		game->cub = mlx_new_image(game->mlx, 800, 800);
		if (!game->cub)
			ft_error();
		mlx_image_to_window(game->mlx, game->minimap, 0, 0);
		mlx_image_to_window(game->mlx, game->cub, 0, 0);
		mlx_loop_hook(game->mlx, ft_hook, game);
		mlx_loop(game->mlx);
		mlx_terminate(game->mlx);
		printf("game over\n");
		free_all(&data);
	}
	else
		print_error("Usage : ./cub3d maps/map.cub", 1, NULL);
	return (0);
}
