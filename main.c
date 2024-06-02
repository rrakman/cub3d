/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:05:18 by rrakman           #+#    #+#             */
/*   Updated: 2024/06/02 17:34:09 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(void *param)
{
    t_game *game;
    int	x;
    int	y;

    game = (t_game *)param;
    y = 0;
    if (!game->minimap)
        ft_error();
    while (y < game->map_width)
    {
        x = 0;
        if (game->data->map[y] == NULL) {
            break;
        }
        while (x < ft_strlen(game->data->map[y]))
        {
            if (game->data->map[y][x] == '1')
                draw_square(game, x * game->tale_size, y * game->tale_size, BLACK);
			else if(game->data->map[y][x] == '0' || game->data->map[y][x] == 'W' || \
				game->data->map[y][x] == 'E' || game->data->map[y][x] == 'N' || game->data->map[y][x] == 'S')
                draw_square(game, x * game->tale_size, y * game->tale_size, WHITE);
            x++;
        }
        y++;
    }
}

void	draw_line(mlx_image_t *img,int x0, int y0, int x1, int y1) 
{ 
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    float Xinc = dx / (float)steps; 
    float Yinc = dy / (float)steps; 

    float X = x0; 
    float Y = y0; 
    int i = 0;
	while(i <= steps)
	{
		mlx_put_pixel(img,round(X), round(Y), GRAY);
        X += Xinc;
        Y += Yinc;
		i++;
    }
}

int	wall_hit(t_game *game,float x, float y)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = (int)(x / game->tale_size);
	y_m = (int)(y / game->tale_size);
	if ((y_m >= game->map_height || x_m >= game->map_width))
		return (0);
	if (game->data->map[y_m] && x_m <= (int)strlen(game->data->map[y_m]))
		if (game->data->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

int	inter_check(float tale_size, float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += tale_size;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
		{
			*inter += tale_size;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	check_angle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

float horizontal_intersection(t_game *game)
{
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = game->tale_size;
	x_step = game->tale_size / tan(game->ray->angle);
	game->ray->y = floor(game->player_yp / game->tale_size) * game->tale_size;
	pixel = inter_check(game->tale_size, game->ray->angle, &game->ray->y, &y_step, 1);
	game->ray->x = game->player_xp + (game->ray->y - game->player_yp) / tan(game->ray->angle);
	if ((check_angle(game->ray->angle, 'y') && x_step > 0) || (!check_angle(game->ray->angle, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(game,game->ray->x, game->ray->y - pixel))
	{
		game->ray->x += x_step;
		game->ray->y += y_step;
	}
	return (sqrt(pow(game->ray->x - game->player_xp, 2) + pow(game->ray->y - game->player_yp, 2)));
}

float	vertical_intersection(t_game *game)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = game->tale_size; 
	y_step = game->tale_size * tan(game->ray->angle);
	v_x = floor(game->player_xp / game->tale_size) * game->tale_size;
	pixel = inter_check(game->tale_size, game->ray->angle, &v_x, &x_step, 0);
	v_y = game->player_yp + (v_x - game->player_xp) * tan(game->ray->angle);
	if ((check_angle(game->ray->angle, 'x') && y_step < 0) || (!check_angle(game->ray->angle, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(game,v_x - pixel, v_y))
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - game->player_xp, 2) + pow(v_y - game->player_yp, 2)));
}

void draw_fov(t_game *game, float chose)
{
	float x = game->player_xp + chose * cos(game->ray->angle);
	float y = game->player_yp + chose * sin(game->ray->angle);
	draw_line(game->minimap, game->player_xp, game->player_yp, x, y);
}

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
	int color;

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

void render_walls(t_game *game, float distance, int ray)
{
	float	wall_h;
	float	b_pix;
	float	t_pix;

	float angle = game->ray->angle - game->angle;
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
	int ray;
	float horiz_i;
	float vert_i;
	float chose;
	normalize_angle(&game->angle);
	game->ray->angle = game->angle - game->fov_rd / 2;
	ray = 0;
	while(ray < 800)
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

void draw_player(t_game *game)
{
    int	i_start;
    int	j_start;
    int	i_end;
    int	j_end;
	int i;

	int player_square_size = game->tale_size / 4;
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
            mlx_put_pixel(game->minimap, i, j, YELLOW);
			j++;
		}
		i++;
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
	game->player_square_size_half = game->tale_size / 8;
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
		game->minimap = mlx_new_image(game->mlx, game->map_width * game->tale_size , game->map_height * game->tale_size);
		game->cub = mlx_new_image(game->mlx, 800, 800);
		if (!game->cub)
			ft_error();
		mlx_image_to_window(game->mlx, game->minimap, 0, 0);
		mlx_image_to_window(game->mlx, game->cub, 0, 0);
		mlx_loop_hook(game->mlx, ft_hook, game);
		mlx_loop(game->mlx);
		mlx_terminate(game->mlx);
		free_all(&data);
	}
	else
		print_error("Usage : ./cub3d maps/map.cub", 1, NULL);
	return (0);
}
