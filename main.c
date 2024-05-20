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
	printf("%s\n", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int border_color;

	i = 0;
	border_color = ft_pixel(0x0A,0x4A,0xFA,0xFF);
	while (i < game->player_size)
	{
		j = 0;
		while (j < game->player_size)
		{
			if (i == 0 || j == 0 || i == game->player_size - 1 || j == game->player_size - 1)
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
    int color_floor;
    int	x;
    int	y;

    color_wall = ft_pixel(0x00, 0x00, 0x00, 0xFF);
    color_floor = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
    y = 0;
    if (!game->minimap)
        ft_error();
    while (y < game->map_width)
    {
        x = 0;
        if (game->map[y] == NULL) {
            break;
        }
        int row_length = ft_strlen(game->map[y]);  // Calculate the length of the current row
        while (x < row_length)
        {
            if (game->map[y][x] == '1')
                draw_square(game, x * game->player_size, y * game->player_size, color_wall);
			else if(game->map[y][x] == '0' || game->map[y][x] == 'W' || \
				game->map[y][x] == 'E' || game->map[y][x] == 'N' || game->map[y][x] == 'S')
                draw_square(game, x * game->player_size, y * game->player_size, color_floor);
            x++;
        }
        y++;
    }
}

void	draw_line(mlx_image_t *img, int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1);
	int sx = x1 < x2 ? 1 : -1;
	int dy = -abs(y2 - y1);
	int sy = y1 < y2 ? 1 : -1;
	int err = dx + dy;
	int e2;
	while (1)
	{
 		mlx_put_pixel(img, x1, y1, ft_pixel(0x00, 0x00, 0xFF, 0xFF));
		if (x1 == x2 && y1 == y2)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x1 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void draw_angle(t_game *game)
{
	float x2;
	float y2;
	x2 = game->player_xp + 20 * cos(game->angle);
	y2 = game->player_yp + 20 * sin(game->angle);
	draw_line(game->minimap, game->player_xp, game->player_yp, x2, y2);
}

void draw_player(t_game *game)
{
    int	i_start;
    int	j_start;
    int	i_end;
    int	j_end;
    int player_color;
	int i;

    player_color = ft_pixel(0xAA,0x00,0xFA,0xFF);
	int player_square_size = game->player_size / 4;
    i_start = game->player_xp - player_square_size / 2;
    j_start = game->player_yp - player_square_size / 2;
    i_end = game->player_xp + player_square_size / 2;
    j_end = game->player_yp + player_square_size / 2;

	i = i_start;
    while (i < i_end)
    {
		int j = j_start;
        while (j < j_end)
        {
            mlx_put_pixel(game->minimap, i, j, player_color);
			j++;
		}
		i++;
    }
	draw_angle(game);
}

int len2d(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}


int biggestline(char **arr)
{
	int i;
	int biggest;

	i = 0;
	biggest = 0;
	while (arr[i])
	{
		if (ft_strlen(arr[i]) > biggest)
			biggest = strlen(arr[i]);
		i++;
	}
	return (biggest);
}

void fill_map(t_game *game, t_map *data)
{
	game->map = data->map;
	game->player_x = data->player_x;
	game->player_y = data->player_y;
	printf("player x = %d\n", game->player_x);
	printf("player y = %d\n", game->player_y);
	game->map_height = len2d(game->map);
	game->map_width = biggestline(game->map);
	int test = 500 / game->map_width;
	int test2 = 200 / game->map_height;
	game->player_size = test < test2 ? test : test2;
	game->player_xp = (game->player_x * game->player_size) + (game->player_size / 2); // set player pos x in px setting him in the middle of the cube
	game->player_yp = (game->player_y * game->player_size) + (game->player_size / 2);
	game->angle = M_PI / 2;
	
	
	
}

int	main(int ac, char **av)
{
	t_map	data;
	t_game	*game;

	if (ac == 2)
	{
		first_check(av, &data);
		map_check(&data);
		print_all(&data);
		
		game = malloc(sizeof(t_game));
		game->mlx = mlx_init(1400, 1000, "CUB3D", 0);
		if (!game->mlx)
			ft_error();
		fill_map(game, &data);
		game->minimap = mlx_new_image(game->mlx, game->map_width * game->player_size, game->map_height * game->player_size);
		if (!game->minimap)
			ft_error();
		mlx_image_to_window(game->mlx, game->minimap, 0, 0);
		mlx_loop_hook(game->mlx, ft_hook, game);
		mlx_loop(game->mlx);
		mlx_terminate(game->mlx);
		
		free_all(&data);
	}
	else
		print_error("the programme he need just the map \n", 1, NULL);
	return (0);

}
