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
