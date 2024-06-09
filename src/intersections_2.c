/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakman <rrakman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:44:38 by rrakman           #+#    #+#             */
/*   Updated: 2024/06/09 17:47:19 by rrakman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calcul_intersections(t_game *g, double *h_i, double *v_i, double *chose)
{
	*h_i = horizontal_intersection(g);
	*v_i = vertical_intersection(g);
	if (*v_i <= *h_i)
	{
		g->ray->x = g->ray->x_v;
		g->ray->y = g->ray->y_v;
		g->ray->flag = 1;
		*chose = *v_i;
	}
	else
	{
		g->ray->x = g->ray->x_h;
		g->ray->y = g->ray->y_h;
		*chose = *h_i;
		g->ray->flag = 0;
	}
}
