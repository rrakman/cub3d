/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-moue <hel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:30:38 by hel-moue          #+#    #+#             */
/*   Updated: 2024/05/15 21:30:38 by hel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_error(char *str, int ext, t_map *data)
{
	if (data)
		free_all(data);
	printf("\x1b[31mError\n\x1b[0m%s\n", str);
	exit(ext);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (path[i - 1] == 'b' && path[i - 2] == 'u'
		&& path[i - 3] == 'c' && path[i - 4] == '.')
		return (0);
	return (1);
}

void	first_check(char **argv, t_map *data)
{
	data->file_path = argv[1];
	if (check_path(data->file_path))
		print_error("File extension must finish by .cub", 1, NULL);
	data->fd_file = open(data->file_path, O_RDONLY);
	if (data->fd_file == -1)
		print_error("Error Can't open the file", 1, NULL);
	return ;
}

void	map_check(t_map *data)
{
	init_struct(&data);
	file_to_arr(&data);
	player_check(data);
	floodfill_check(&data);
	data->texture = malloc(sizeof(t_texture));
	if (!data->texture)
		print_error("Malloc failed", 1, data);
	data->texture->no = mlx_load_png(data->no);
	data->texture->so = mlx_load_png(data->so);
	data->texture->we = mlx_load_png(data->we);
	data->texture->ea = mlx_load_png(data->ea);
	if (!data->texture->no || !data->texture->so \
		|| !data->texture->we || !data->texture->ea)
		print_error("Texture not found", 1, data);
	if (data->texture->no->height != 32 || data->texture->no->width != 32 \
		|| data->texture->so->height != 32 || data->texture->so->width != 32 \
		|| data->texture->we->height != 32 || data->texture->we->width != 32 \
		|| data->texture->ea->height != 32 || data->texture->ea->width != 32)
		print_error("Texture must be 32x32", 1, data);
}
