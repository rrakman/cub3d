/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:15:26 by rrakman           #+#    #+#             */
/*   Updated: 2024/05/12 18:38:06rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error()
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	ft_hook(void *game)
{
	t_game	*mlx;

	mlx = (t_game *)game;

	if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx->mlx);
	if (mlx_is_key_down(mlx->mlx,MLX_KEY_DOWN))
		mlx->player_yp += 5;
	if (mlx_is_key_down(mlx->mlx,MLX_KEY_UP))
		mlx->player_yp -= 5;
	if (mlx_is_key_down(mlx->mlx,MLX_KEY_LEFT))
		mlx->player_xp -= 5;
	if (mlx_is_key_down(mlx->mlx,MLX_KEY_RIGHT))
		mlx->player_xp += 5;
	
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void draw_circle(mlx_image_t* image, int x0, int y0, int radius, int color)
{
	int i;
    int x;
    int y;
    int err;
	err = 0;
	x = radius;
	y = 0;
    while (x >= y)
    {
		i = x0 - x;
        while (i <= x0 + x)
        {
            mlx_put_pixel(image, i, y0 + y, color);
            mlx_put_pixel(image, i, y0 - y, color);
			i++;
        }
		i = x0 - y;
        while (i <= x0 + y)
        {
            mlx_put_pixel(image, i, y0 + x, color);
            mlx_put_pixel(image, i, y0 - x, color);
			i++;
        }

        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }

        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}


void draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int border_color;

	i = 0;
	border_color = ft_pixel(0xFF,0xFF,0xFF,0xFF);
	while (i < CUBE_SIZE)
	{
		j = 0;
		while (j < CUBE_SIZE)
		{
			if (i == 0 || j == 0 || i == CUBE_SIZE - 1 || j == CUBE_SIZE - 1)
				mlx_put_pixel(game->minimap, x + i, y + j, border_color);
			else
				mlx_put_pixel(game->minimap, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(void *param)
{
	t_game *game;

	game = (t_game *)param;

	int	color_wall;
	int	x;
	int	y;
	int color_floor;

	game->minimap = mlx_new_image(game->mlx, MAP_LENGTH * CUBE_SIZE, MAP_WIDTH * CUBE_SIZE);
	if (!game->minimap)
		ft_error();
	color_wall = ft_pixel(0x00, 0x00, 0x00, 0xFF);
	color_floor = ft_pixel(0x40, 0x02, 0x50, 0xFF);
	y = 0;
	while (y < MAP_WIDTH)
	{
		x = 0;
		while (x < MAP_LENGTH)
		{
			if (game->map[y][x] == '1')
				draw_square(game, x * CUBE_SIZE, y * CUBE_SIZE, color_wall);
			else
				draw_square(game, x * CUBE_SIZE, y * CUBE_SIZE, color_floor);
			x++;
		}
		y++;
	}
	int color = ft_pixel(0xAF, 0xFF,0x00, 0xFF);
	
	draw_circle(game->minimap, game->player_xp + 25, game->player_yp + 25, 10, color);
	mlx_image_to_window(game->mlx, game->minimap, 0, 0);
}

void fill_map(t_game *game)
{
	game->map = malloc(sizeof(char *) * 10);
	game->map[0] = "1111111111111111111111111";
	game->map[1] = "10000000000000000000000P1";
	game->map[2] = "1000000000011000000000001";
	game->map[3] = "1000000000000000000000001";
	game->map[4] = "1000000000000000000000001";
	game->map[5] = "1000000000000000000000001";
	game->map[6] = "1000000000000000000000001";
	game->map[7] = "1000000000000000000000001";
	game->map[8] = "1000000000000000000000001";
	game->map[9] = "1111111111111111111111111";
	game->player_x = 1;
	game->player_y = 7;
	game->player_xp = game->player_x * CUBE_SIZE;
	game->player_yp = game->player_y * CUBE_SIZE;
}

int	main(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	game->mlx = mlx_init(25*50, 10*50, "CUB3D", 0);
	fill_map(game);
	if (!game->mlx)
		ft_error();
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop_hook(game->mlx, draw_minimap,game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
