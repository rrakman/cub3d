/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:21:22 by hel-moue          #+#    #+#             */
/*   Updated: 2024/06/04 14:46:05 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_close_map(char **map, int i, int j, t_map *data)
{
	if (i == 0 || i == data->map_size - 1 || j == 0 
		|| j == ft_strlen(map[i]) - 1)
		print_error("Map not closed", 1, data);
	if (map[i - 1][j] == 0 || map[i + 1][j] == 0 
		|| map[i][j - 1] == 0 || map[i][j + 1] == 0)
		print_error("Map not closed", 1, data);
	if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' 
		|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
		print_error("Map not closed", 1, data);
	if (map[i - 1][j] == '\n' || map[i + 1][j] == '\n' 
		|| map[i][j - 1] == '\n' || map[i][j + 1] == '\n')
		print_error("Map not closed", 1, data);
}

void	check_valid_map(char **map, t_map *data)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '.')
				check_close_map(map, i, j, data);
		}
	}
}

int	is_digit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	check_ntwo(char *str, t_map *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == ',' && str[i + 1] == ',') \
			|| (str[i] == ',' && (str[i + 1] == '\0' || str[i + 1] == '\n')))
			print_error("RGB value must be in RGB format[,]", 1, data);
		i++;
	}
}

void	check_floor(t_map **data, char *str)
{
	int		i;
	char	*str2;
	char	**rgb;
	char	*tmp;

	i = -1;
	if ((*data)->floor_rgb)
		print_error("Floor color already defined", 1, *data);
	str2 = ft_strdup(str + 2);
	tmp = str2;
	str2 = ft_strtrim(str2, " \t");
	free(tmp);
	check_ntwo(str2, *data);
	rgb = ft_split(str2, ',');
	check_rgb(rgb, data, &i);
	i = -1;
	(*data)->floor_rgb = (int *)ft_calloc(sizeof(int), 3);
	while (++i < 3)
	{
		(*data)->floor_rgb[i] = ft_atoi(rgb[i]);
		if ((*data)->floor_rgb[i] < 0 || (*data)->floor_rgb[i] > 255)
			print_error("RGB value must be between 0 and 255", 1, *data);
	}
	free_norm(rgb, str2);
}
