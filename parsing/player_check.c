/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:59:28 by hel-moue          #+#    #+#             */
/*   Updated: 2024/06/03 22:38:24 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_no_player(t_map *data)
{
	if (data->player_x == -1 || data->player_y == -1)
		print_error("No player", 1, NULL);
}

void	player_check(t_map *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				if (data->player_x != -1 || data->player_y != -1)
					print_error("Multiple player", 1, data);
				data->player_x = j;
				data->player_y = i;
				data->player_dir = data->map[i][j];
			}
			else if (data->map[i][j] != '1' && data->map[i][j] != '0'
				&& data->map[i][j] != ' ' && data->map[i][j] != '\n'
				&& data->map[i][j] != 13 && data->map[i][j] != '\t')
				print_error("Invalid character in map", 1, data);
		}
	}
	check_no_player(data);
}
