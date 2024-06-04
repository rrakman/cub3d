/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:06:00 by hel-moue          #+#    #+#             */
/*   Updated: 2024/06/04 13:16:56 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_line_one(char *str)
{
	if (str[0] != 'N' && str[0] != 'S' 
		&& str[0] != 'W' && str[0] != 'E' 
		&& str[0] != 'F' && str[0] != 'C' 
		&& str[0] != '1' && str[0] != '0' 
		&& str[0] != '\0' && str[0] != '\n' 
		&& str[0] != 13)
		print_error("Invalid Map [ERROR 15]", 1, NULL);
}

int	check_line_two(char *str)
{
	if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
		return (1);
	else if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ')
		return (1);
	else if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
		return (1);
	else if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
		return (1);
	else if (str[0] == 'F' && str[1] == ' ')
		return (1);
	else if (str[0] == 'C' && str[1] == ' ')
		return (1);
	return (0);
}

void	check_n_s_w_e(t_map **data, char *str)
{
	if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
		check_no(data, str);
	else if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ')
		check_so(data, str);
	else if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
		check_we(data, str);
	else if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
		check_ea(data, str);
	else if (str[0] == 'F' && str[1] == ' ')
		check_floor(data, str);
	else if (str[0] == 'C' && str[1] == ' ')
		check_ceiling(data, str);
}

bool	data_check(t_map **data)
{
	if ((*data)->no && (*data)->so && (*data)->we 
		&& (*data)->ea && (*data)->floor_rgb && (*data)->ceiling_rgb)
		return (true);
	return (false);
}

void	file_to_arr(t_map **data)
{
	char	*str;
	int		i;

	i = 0;
	(*data)->data_size = data_count((*data)->fd_file);
	(*data)->file_data = alloc_data((*data)->data_size);
	(*data)->fd_file = open((*data)->file_path, O_RDONLY);
	(*data)->file_data[i] = get_next_line((*data)->fd_file);
	while ((*data)->file_data[i])
	{
		str = ft_strtrim((*data)->file_data[i], " \t\n");
		check_line_one(str);
		all_checks(data, str, i);
		i++;
		free(str);
		(*data)->file_data[i] = get_next_line((*data)->fd_file);
	}
	close((*data)->fd_file);
	return ;
}
