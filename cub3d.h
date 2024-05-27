/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:05:18 by rrakman           #+#    #+#             */
/*   Updated: 2024/05/27 16:34:36 by rrakman          ###   ########.fr       */
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
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# define DARK_BLUE 191970
# define DARK_ORANGE 0x483C32
# define DARK_GREEN 0x3e00ed

# define ERROR 1
# define WHITE 0xFFFFFFFF
# define BLUE 0xFFFF
# define RED 0xFF0000FF
# define PURPLE 0xFF00FFFF
# define YELLOW 0xFFFF
# define BLACK 0x00000000

# define GREEN 0x00FF00FF
# define ORANGE 0xFFA500FF
# define PINK 0xFF69B4FF
# define CYAN 0x00FFFFFF
# define GRAY 0x808080FF
# define BROWN 0xA52A2AFF

#define FOV 60
#define S_W 800

typedef struct s_map
{
	char	*file_path;
	int		fd_file;
	char	**file_data;
	char	**data_filtered;
	int 	data_size;

	char	**map;
	int		map_size;
	bool	map_exist;
	bool	map_finsh;
	
	int		player_x;
	int		player_y;
	char 	player_dir;

	char	*no;
	char	*so;
	char	*we;
	char	*ea;

	int 	*floor_rgb;
	int		*ceiling_rgb;

}t_map;

typedef struct s_ray
{
	float angle;
	float distance;
	float x;
	float y;
	int flag;
}   t_ray;



typedef struct s_game
{
	mlx_t* mlx;
	mlx_image_t* minimap;
	mlx_image_t* cub;
	char **map;
	int player_x;
	int player_y;
	float player_xp;
	float player_yp;
	float angle;
	int map_height;
	int map_width;
	float tale_size;
	int player_square_size_half;
	float fov_rd;
	float increment;
	t_ray *ray;
}   t_game;

void	draw_minimap(void *param);
void	draw_player(t_game *game);
void	cast_rays(t_game *game);
void	ft_hook(void *game);
void	go_right(t_game *mlx);
void	go_left(t_game *mlx);
void	go_up(t_game *mlx);
void	go_down(t_game *mlx);



// maths
float	degree_to_radian(float degree);
void	normalize_angle(float *angle);

//tools
void	ft_error();
void draw_square(t_game *game, int x, int y, int color);
void define_angle(t_game *game, char dir);
int biggestline(char **arr);
int len2d(char **arr);


// parsing 

char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
int		ft_strchr(char	*s1, char s2);
void	*ft_calloc(unsigned int size, unsigned int len);
char	*get_next_line(int fd);

void	init_struct(t_map **data);
void	file_to_arr(t_map **data);
void	check_no(t_map **data, char *str);
void	check_so(t_map **data, char *str);
void	check_we(t_map **data, char *str);
void	check_ea(t_map **data, char *str);
void	check_floor(t_map **data, char *str);
void	check_ceiling(t_map **data, char *str);
void	print_error(char *str, int i, t_map *data);
char	*ft_strtrim(char *s1, char *set);
char	**ft_split(char *s, char c);
int		is_digit_str(char *str);
int		ft_atoi(char *str);
char	*ft_strdup(char *str);
int		data_count(int fd);
char	**alloc_data(int size);
void	check_valid_map(char **map, t_map *data);
void	check_floor(t_map **data, char *str);
void	check_ceiling(t_map **data, char *str);
void	check_n_s_w_e(t_map **data, char *str);
bool	data_check(t_map **data);
void	file_to_arr(t_map **data);
void	floodfill_check(t_map **data);
void	check_theline_map(char *str, t_map *data);
void	player_check(t_map *data);
void	flood_fill(char **map, int x, int y, int map_size);
void	map_check(t_map *data);
void	check_ceiling(t_map **data, char *str);
void	print_all(t_map *data);
void	free_all(t_map *data);
void	first_check(char **argv, t_map *data);
int	check_path(char *path);
void	print_error(char *str, int ext, t_map *data);

#endif