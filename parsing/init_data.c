/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:01:23 by hel-moue          #+#    #+#             */
/*   Updated: 2024/06/09 16:11:57 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_struct(t_map **data)
{
	(*data)->file_data = NULL;
	(*data)->data_size = 0;
	(*data)->no = NULL;
	(*data)->so = NULL;
	(*data)->we = NULL;
	(*data)->ea = NULL;
	(*data)->floor_rgb = NULL;
	(*data)->ceiling_rgb = NULL;
	(*data)->map = NULL;
	(*data)->map_size = 0;
	(*data)->map_exist = false;
	(*data)->map_finsh = false;
	(*data)->player_x = -1;
	(*data)->player_y = -1;
	(*data)->player_dir = 0;
}

int	data_count(int fd)
{
	int		count;
	int		i;
	char	*line;

	count = 0;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	if (count == 0)
		print_error("Empty file\n", 1, NULL);
	close(fd);
	return (count);
}

char	**alloc_data(int size)
{
	char	**data;
	int		i;

	i = 0;
	data = (char **)malloc(sizeof(char *) * (size + 1));
	if (!data)
		print_error("Malloc failed [ERROR 7]", 1, NULL);
	while (i < size)
	{
		data[i] = NULL;
		i++;
	}
	data[i] = NULL;
	return (data);
}

void	more_free(t_map *data)
{
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
}

void	free_all(t_map *data)
{
	int	i;

	i = -1;
	more_free(data);
	if (data->floor_rgb)
		free(data->floor_rgb);
	if (data->ceiling_rgb)
		free(data->ceiling_rgb);
	if (data->map)
	{
		while (data->map[++i])
		{
			free(data->map[i]);
			data->map[i] = NULL;
		}
		free(data->map);
		data->map = NULL;
	}
}
