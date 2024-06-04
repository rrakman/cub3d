/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:16:40 by rrakman           #+#    #+#             */
/*   Updated: 2024/06/04 13:26:12 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	go_down(t_game *mlx)
{
	float	new_xp;
	float	new_yp;
	bool	map_coalision;

	new_xp = mlx->player_xp - 1 * cos(mlx->angle);
	new_yp = mlx->player_yp - 1 * sin(mlx->angle);
	map_coalision = mapcheck(mlx, new_xp, new_yp);
	if (!map_coalision)
	{
		mlx->player_xp = new_xp;
		mlx->player_yp = new_yp;
	}
}

void	go_up(t_game *mlx)
{
	float	new_xp;
	float	new_yp;
	bool	map_coalision;

	new_xp = mlx->player_xp + 1 * cos(mlx->angle);
	new_yp = mlx->player_yp + 1 * sin(mlx->angle);
	map_coalision = mapcheck(mlx, new_xp, new_yp);
	if (!map_coalision)
	{
		mlx->player_xp = new_xp;
		mlx->player_yp = new_yp;
	}
}

void	go_left(t_game *mlx)
{
	float	new_xp;
	float	new_yp;
	bool	map_coalision;

	new_xp = mlx->player_xp + 1 * sin(mlx->angle);
	new_yp = mlx->player_yp - 1 * cos(mlx->angle);
	map_coalision = mapcheck(mlx, new_xp, new_yp);
	if (!map_coalision)
	{
		mlx->player_xp = new_xp;
		mlx->player_yp = new_yp;
	}
}

void	go_right(t_game *mlx)
{
	float	new_xp;
	float	new_yp;
	bool	map_coalision;

	new_xp = mlx->player_xp - 1 * sin(mlx->angle);
	new_yp = mlx->player_yp + 1 * cos(mlx->angle);
	map_coalision = mapcheck(mlx, new_xp, new_yp);
	if (!map_coalision)
	{
		mlx->player_xp = new_xp;
		mlx->player_yp = new_yp;
	}
}
