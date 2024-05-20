/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:29:08 by hel-moue          #+#    #+#             */
/*   Updated: 2024/05/20 19:55:37 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	flood_fill(char **map, int player_x, int player_y, int map_size)
{
	if (player_x < 0 || player_x >= map_size || player_y < 0 
		|| player_y >= ft_strlen(map[player_x])
		|| map[player_x][player_y] == '1' || map[player_x][player_y] == ' '
		|| map[player_x][player_y] == '.' || map[player_x][player_y] == '\n')
		return ;
	map[player_x][player_y] = '.';
	flood_fill(map, player_x + 1, player_y, map_size);
	flood_fill(map, player_x - 1, player_y, map_size);
	flood_fill(map, player_x, player_y + 1, map_size);
	flood_fill(map, player_x, player_y - 1, map_size);
}



void	floodfill_check(t_map **data)
{
	char	**mapcpy;
	int		i; 

	// pause();
	mapcpy = (char **)ft_calloc(sizeof(char *), (*data)->map_size + 1);
	i = 0;
	while (i < (*data)->map_size)
	{
		mapcpy[i] = ft_strdup((*data)->map[i]);
		i++;
	}
	flood_fill(mapcpy, (*data)->player_x, (*data)->player_y, (*data)->map_size);
	check_valid_map(mapcpy, *data);
	i = 0;
	while (i < (*data)->map_size)
	{
		free(mapcpy[i]);
		i++;
	}
	free(mapcpy);
}

void	check_rgb(char **rgb, t_map **data, int *i)
{
	while (rgb[*i])
	{
		if (!is_digit_str(rgb[*i]))
			print_error("RGB value must be a number\n", 1, *data);
		(*i)++;
	}
}

void	check_ceiling(t_map **data, char *str)
{
	int		i;
	int		j;
	char	*str2;
	char	**rgb;

	i = 0;
	j = 0;
	if ((*data)->ceiling_rgb)
		print_error("Ceiling color already defined\n", 1, *data);
	str2 = ft_strtrim(ft_strdup(str + 2), " \t");
	rgb = ft_split(str2, ',');
	check_rgb(rgb, data, &i);
	if (i != 3)
		print_error("Ceiling color must be in RGB format\n", 1, *data);
	(*data)->ceiling_rgb = (int *)ft_calloc(sizeof(int), 3);
	while (j < 3)
	{
		(*data)->ceiling_rgb[j] = ft_atoi(rgb[j]);
		if ((*data)->ceiling_rgb[j] < 0 || (*data)->ceiling_rgb[j] > 255)
			print_error("RGB value must be between 0 and 255\n", 1, *data);
		j++;
	}
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
	free(str2);
}
