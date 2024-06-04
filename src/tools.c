/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:12:07 by rrakman           #+#    #+#             */
/*   Updated: 2024/06/04 13:26:19 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(void)
{
	printf("%s\n", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	ft_pixel(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	len2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	biggestline(char **arr)
{
	int	i;
	int	biggest;

	i = 0;
	biggest = 0;
	while (arr[i])
	{
		if (ft_strlen(arr[i]) > biggest)
			biggest = strlen(arr[i]);
		i++;
	}
	return (biggest);
}

void	define_angle(t_game *game, char dir)
{
	if (dir == 'N')
		game->angle = 3 * M_PI_2;
	else if (dir == 'E')
		game->angle = M_PI_2;
	else if (dir == 'S')
		game->angle = M_PI_2;
	else if (dir == 'W')
		game->angle = M_PI;
}
