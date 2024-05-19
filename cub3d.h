/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:05:18 by rrakman           #+#    #+#             */
/*   Updated: 2024/05/19 19:12:41 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../MLX42/include/MLX42/MLX42.h"
#include "math.h"


#define MAP_LENGTH 16
#define MAP_WIDTH 10
#define CUBE_SIZE 32
// #define PLAYER_SIZE 2
#define FOV 60

typedef struct s_game
{
	mlx_t* mlx;
	mlx_image_t* minimap;
	char **map;
	int player_x;
	int player_y;
	float player_xp; // player pos x in px
	float player_yp; // player pos Y in px
	float angle;
	int map_length;
	int map_width;
	int player_size;
}   t_game;

void	draw_minimap(void *param);
void	draw_player(t_game *game);

void	ft_hook(void *game);
void	go_right(t_game *mlx, int player_square_size);
void	go_left(t_game *mlx, int player_square_size);
void	go_up(t_game *mlx, int player_square_size);
void	go_down(t_game *mlx, int player_square_size);


// maths
float degree_to_radian(float degree);

#endif