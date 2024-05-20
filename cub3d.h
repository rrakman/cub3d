/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:05:18 by rrakman           #+#    #+#             */
/*   Updated: 2024/05/20 20:15:29 by rrakman          ###   ########.fr       */
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


#define MAP_LENGTH 16
#define MAP_WIDTH 10
#define CUBE_SIZE 32
#define FOV 60


//---------cub3d Header---------//
typedef struct s_map
{
	char	*file_path;
	int		fd_file;
	char	**file_data;
	char	**data_filtered;
	int 	data_size;

	char	**map;//
	int		map_size;
	bool	map_exist;
	bool	map_finsh;
	
	int		player_x;//
	int		player_y;//
	char 	player_dir;//

	char	*no;//
	char	*so;//
	char	*we;//
	char	*ea;//

	int 	*floor_rgb;//
	int		*ceiling_rgb;//

}t_map;




typedef struct s_game
{
	mlx_t* mlx;
	mlx_image_t* minimap;
	char **map;
	int player_x;
	int player_y;
	float player_xp;
	float player_yp;
	float angle;
	int map_height;
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