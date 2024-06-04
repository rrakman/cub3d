/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:15:53 by rrakman           #+#    #+#             */
/*   Updated: 2024/06/04 13:16:31 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	all_checks(t_map **data, char *str, int i)
{
	if (check_line_two(str) == 1)
		check_n_s_w_e(data, str);
	if (check_line_two(str) == 0 && str[0] != '\n'\
			&& str[0] != '\0' && str[0] != '0' && str[0] != '1')
		print_error("Invalid Map [ERROR 14]", 1, *data);
	else if ((str[0] == '1' || str[0] == '0'))
	{
		if (data_check(data) == true)
		{
			if (!(*data)->map)
			{
				(*data)->map = alloc_data((*data)->data_size - i);
				(*data)->map_exist = true;
			}
			if ((*data)->map_finsh == true)
				print_error("Map not at the end", 1, *data);
			(*data)->map[(*data)->map_size]
				= ft_strdup((*data)->file_data[i]);
			(*data)->map_size++;
		}
		else
			print_error("Invalid Map [ERROR 16]", 1, *data);
	}
	else if (str[0] == '\n' && (*data)->map_exist == true)
		(*data)->map_finsh = true;
}
