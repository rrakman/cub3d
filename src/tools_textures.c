/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:48:08 by rrakman           #+#    #+#             */
/*   Updated: 2024/06/09 17:51:12 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

mlx_texture_t	*get_right_texture(t_game *game)
{
	if (game->ray->flag)
	{
		if (cos(game->ray->angle) > 0)
			return (game->data->texture->we);
		else
			return (game->data->texture->ea);
	}
	else
	{
		if (sin(game->ray->angle) > 0)
			return (game->data->texture->no);
		else
			return (game->data->texture->so);
	}
}

int	get_color_at(int offset_x, int offset_y, mlx_texture_t *texture)
{
	int	offset;
	int	red;
	int	green;
	int	blue;
	int	alpha;

	offset = (offset_y * texture->width + offset_x) * 4;
	red = texture->pixels[offset++];
	green = texture->pixels[offset++];
	blue = texture->pixels[offset++];
	alpha = texture->pixels[offset++];
	return (ft_pixel(red, green, blue, alpha));
}
