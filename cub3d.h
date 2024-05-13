/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:05:18 by rrakman           #+#    #+#             */
/*   Updated: 2024/05/14 00:29:57 by rrakman          ###   ########.fr       */
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
#define WIDTH 1000
#define HEIGHT 1000

#define MAP_LENGTH 25
#define MAP_WIDTH 10
#define CUBE_SIZE 50

typedef struct s_game
{
    mlx_t* mlx;
	mlx_image_t* minimap;
	char **map;
	int player_x;
	int player_y;
	int player_xp; // player pos x in px
	int player_yp; // player pos Y in px
}   t_game;


#endif