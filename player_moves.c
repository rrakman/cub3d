/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:27:49 by rrakman           #+#    #+#             */
/*   Updated: 2024/05/27 17:15:59 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

bool mapcheck(t_game *mlx, float new_xp, float new_yp)
{	
	int top_left_x = (int)(new_xp - mlx->player_square_size_half) / mlx->tale_size;
	int top_right_x = (int)(new_xp + mlx->player_square_size_half) / mlx->tale_size;
	int top_left_y = (int)(new_yp - mlx->player_square_size_half) / mlx->tale_size;
	int top_right_y = top_left_y;

	int bottom_left_x = (int)(new_xp - mlx->player_square_size_half) / mlx->tale_size;
	int bottom_right_x = (int)(new_xp + mlx->player_square_size_half) / mlx->tale_size;
	int bottom_left_y = (int)(new_yp + mlx->player_square_size_half) / mlx->tale_size;

	if (mlx->map[top_left_y][top_left_x] == '1' ||
		mlx->map[top_right_y][top_right_x] == '1' ||
		mlx->map[bottom_left_y][bottom_left_x] == '1' ||
		mlx->map[bottom_left_y][bottom_right_x] == '1')
		return true;
	return false;
}

void go_down(t_game *mlx)
{
    float new_xp = mlx->player_xp - 1 * cos(mlx->angle);
    float new_yp = mlx->player_yp - 1 * sin(mlx->angle);
	bool map_coalision = mapcheck(mlx, new_xp, new_yp);
    
    if (!map_coalision){
        mlx->player_xp = new_xp;
        mlx->player_yp = new_yp;
    }
}

void go_up(t_game *mlx)
{
    float new_xp = mlx->player_xp + 1 * cos(mlx->angle);
    float new_yp = mlx->player_yp + 1 * sin(mlx->angle);
	bool map_coalision = mapcheck(mlx, new_xp, new_yp);
    
    if (!map_coalision){
        mlx->player_xp = new_xp;
        mlx->player_yp = new_yp;
    }
}

void go_left(t_game *mlx)
{
    float new_xp = mlx->player_xp + 1 * sin(mlx->angle);
	float new_yp = mlx->player_yp - 1 * cos(mlx->angle);
	bool map_coalision = mapcheck(mlx, new_xp, new_yp);
    
    if (!map_coalision){
        mlx->player_xp = new_xp;
        mlx->player_yp = new_yp;
    }
}

void go_right(t_game *mlx)
{
    float new_xp = mlx->player_xp - 1 * sin(mlx->angle);
	float new_yp = mlx->player_yp + 1 * cos(mlx->angle);
	bool map_coalision = mapcheck(mlx, new_xp, new_yp);
    
    if (!map_coalision)
	{
        mlx->player_xp = new_xp;
        mlx->player_yp = new_yp;
    }
}

void	ft_hook(void *game)
{
    t_game	*mlx;

    mlx = (t_game *)game;

    draw_minimap(game);
    draw_player(game);
	cast_rays(game);
    if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx->mlx);
    if (mlx_is_key_down(mlx->mlx,MLX_KEY_DOWN))
        go_down(mlx);
    if (mlx_is_key_down(mlx->mlx,MLX_KEY_UP))
        go_up(mlx);
    if (mlx_is_key_down(mlx->mlx,MLX_KEY_LEFT))
        go_left(mlx);
    if (mlx_is_key_down(mlx->mlx,MLX_KEY_RIGHT))
        go_right(mlx);
	if(mlx_is_key_down(mlx->mlx, MLX_KEY_A))
	{
		if(mlx->angle > degree_to_radian(360))
			mlx->angle -= degree_to_radian(360);
		mlx->angle -= degree_to_radian(1);
	}
	if(mlx_is_key_down(mlx->mlx, MLX_KEY_D))
	{
		if(mlx->angle < 0)
			mlx->angle += degree_to_radian(360);
		mlx->angle += degree_to_radian(1);
	}
}