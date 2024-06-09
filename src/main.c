/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:05:18 by rrakman           #+#    #+#             */
/*   Updated: 2024/06/09 17:43:31 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_map(t_game *game, t_map *data)
{
	game->map = data->map;
	game->player_x = data->player_x;
	game->player_y = data->player_y;
	game->map_height = len2d(game->data->map);
	game->map_width = biggestline(game->data->map);
	game->tale_size = 32;
	game->player_xp = (game->player_x * game->tale_size) + (game->tale_size
			/ 2);
	game->player_yp = (game->player_y * game->tale_size) + (game->tale_size
			/ 2);
	game->pssh = game->tale_size / 12;
	define_angle(game, data->player_dir);
	game->fov_rd = FOV * M_PI / 180;
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
		print_error("Malloc failed", 1, game->data);
	game->increment = (game->fov_rd / 800);
}

void	run_game(t_map *data, t_game *game)
{
	game->data = data;
	fill_map(game, data);
	game->mlx = mlx_init(800, 800, "cub3D", 0);
	if (!game->mlx)
		ft_error();
	game->cub = mlx_new_image(game->mlx, 800, 800);
	if (!game->cub)
		ft_error();
	mlx_image_to_window(game->mlx, game->cub, 0, 0);
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	printf("game over\n");
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
		if (!game)
			ft_error();
		run_game(&data, game);
		free_all(&data);
	}
	else
		print_error("Usage : ./cub3d maps/map.cub", 1, NULL);
	return (0);
}
