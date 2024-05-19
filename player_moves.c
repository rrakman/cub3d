/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:27:49 by rrakman           #+#    #+#             */
/*   Updated: 2024/05/19 16:25:05 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

void go_down(t_game *mlx, int player_square_size)
{
    int player_square_size_half = player_square_size / 2;
    int top_right_x = (mlx->player_xp + player_square_size_half) / CUBE_SIZE;
    int bottom_left_x = (mlx->player_xp - player_square_size_half) / CUBE_SIZE;
    int bottom_left_y = (mlx->player_yp + player_square_size_half + 1) / CUBE_SIZE;

    int bottom_right_x = top_right_x;
    int bottom_right_y = bottom_left_y;
    if (mlx->map[bottom_left_y][bottom_left_x] != '1' &&
        mlx->map[bottom_right_y][bottom_right_x] != '1')
    {
        mlx->player_yp += 1;
    }
}

void go_up(t_game *mlx, int player_square_size)
{
    int player_square_size_half = player_square_size / 2;
    double new_xp = mlx->player_xp + 1 * cos(mlx->angle);
    double new_yp = mlx->player_yp + 1 * sin(mlx->angle);
    int top_left_x = (int)(new_xp - player_square_size_half) / CUBE_SIZE;
    int top_right_x = (int)(new_xp + player_square_size_half) / CUBE_SIZE;
    int top_left_y = (int)(new_yp - player_square_size_half - 1) / CUBE_SIZE;
    int top_right_y = top_left_y;
	
	int bottom_left_x = (int)(new_xp - player_square_size_half) / CUBE_SIZE;
	int bottom_right_x = (int)(new_xp + player_square_size_half) / CUBE_SIZE;
	int bottom_left_y = (int)(new_yp + player_square_size_half) / CUBE_SIZE;
	int bottom_right_y = bottom_left_y;
	
    if (mlx->map[top_left_y][top_left_x] != '1' &&
        mlx->map[top_right_y][top_right_x] != '1' &&
		mlx->map[bottom_left_y][bottom_left_x] != '1' &&
		mlx->map[bottom_right_y][bottom_right_x] != '1')
    {
        mlx->player_xp = new_xp;
        mlx->player_yp = new_yp;
    }
}

// void go_up(t_game *mlx, int player_square_size)
// {
//     int player_square_size_half = player_square_size / 2;
//     int top_left_x = (mlx->player_xp - player_square_size_half) / CUBE_SIZE;
//     int top_right_x = (mlx->player_xp + player_square_size_half) / CUBE_SIZE;
//     int top_left_y = (mlx->player_yp - player_square_size_half - 1) / CUBE_SIZE;
//     int top_right_y = top_left_y;

//     if (mlx->map[top_left_y][top_left_x] != '1' &&
//         mlx->map[top_right_y][top_right_x] != '1')
//     {
//         mlx->player_yp -= 1;
//     }
// }

void go_left(t_game *mlx, int player_square_size)
{
    int new_x = (mlx->player_xp - 1 - player_square_size / 2) / CUBE_SIZE;
    int top_y = (mlx->player_yp - player_square_size / 2) / CUBE_SIZE;
    int bottom_y = (mlx->player_yp + player_square_size / 2) / CUBE_SIZE;

    if (mlx->map[top_y][new_x] != '1' && mlx->map[bottom_y][new_x] != '1')
        mlx->player_xp -= 1;
}

void go_right(t_game *mlx, int player_square_size)
{
    int new_x = (mlx->player_xp + 1 + player_square_size / 2) / CUBE_SIZE;
    int top_y = (mlx->player_yp - player_square_size / 2) / CUBE_SIZE;
    int bottom_y = (mlx->player_yp + player_square_size / 2) / CUBE_SIZE;

    if (mlx->map[top_y][new_x] != '1' && mlx->map[bottom_y][new_x] != '1')
        mlx->player_xp += 1;
}

void	ft_hook(void *game)
{
    t_game	*mlx;

    mlx = (t_game *)game;

    draw_minimap(game);
    draw_player(game);
    int player_square_size = CUBE_SIZE / 4;
    if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx->mlx);
    if (mlx_is_key_down(mlx->mlx,MLX_KEY_DOWN))
        go_down(mlx, player_square_size);
    if (mlx_is_key_down(mlx->mlx,MLX_KEY_UP))
        go_up(mlx, player_square_size);
    if (mlx_is_key_down(mlx->mlx,MLX_KEY_LEFT))
        go_left(mlx, player_square_size);
    if (mlx_is_key_down(mlx->mlx,MLX_KEY_RIGHT))
        go_right(mlx, player_square_size);
	if(mlx_is_key_down(mlx->mlx, MLX_KEY_A))
		mlx->angle -= degree_to_radian(1);
	if(mlx_is_key_down(mlx->mlx, MLX_KEY_D))
		mlx->angle += degree_to_radian(1);
}