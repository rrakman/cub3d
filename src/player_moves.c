/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:27:49 by rrakman           #+#    #+#             */
/*   Updated: 2024/06/09 19:09:27 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	mapcheck(t_game *mlx, float new_xp, float new_yp)
{
	t_player_square	p;

	p.top_left_x = (int)(new_xp - mlx->pssh) / mlx->tale_size;
	p.top_right_x = (int)(new_xp + mlx->pssh) / mlx->tale_size;
	p.top_left_y = (int)(new_yp - mlx->pssh) / mlx->tale_size;
	p.top_right_y = p.top_left_y;
	p.bottom_left_x = (int)(new_xp - mlx->pssh) / mlx->tale_size;
	p.bottom_right_x = (int)(new_xp + mlx->pssh) / mlx->tale_size;
	p.bottom_left_y = (int)(new_yp + mlx->pssh) / mlx->tale_size;
	if (mlx->map[p.top_left_y][p.top_left_x] == '1' ||
		mlx->map[p.top_right_y][p.top_right_x] == '1' ||
		mlx->map[p.bottom_left_y][p.bottom_left_x] == '1' ||
		mlx->map[p.bottom_left_y][p.bottom_right_x] == '1')
		return (true);
	return (false);
}

void	ft_hook(void *game)
{
	t_game	*mlx;

	mlx = (t_game *)game;
	cast_rays(game);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx->mlx);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_S))
		go_down(mlx);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_W))
		go_up(mlx);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_A))
		go_left(mlx);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_D))
		go_right(mlx);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_LEFT))
	{
		normalize_angle(&mlx->angle);
		mlx->angle -= degree_to_radian(2);
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_RIGHT))
	{
		normalize_angle(&mlx->angle);
		mlx->angle += degree_to_radian(2);
	}
}
