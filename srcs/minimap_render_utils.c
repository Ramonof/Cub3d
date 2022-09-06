/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:26:33 by etobias           #+#    #+#             */
/*   Updated: 2022/09/07 02:23:52 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_x_range(t_app *app)
{
	t_minimap	*minimap;
	int			x_extent;

	minimap = &app->minimap;
	x_extent = 0;
	minimap->min_x = (int)app->player.pos_x - minimap->radius;
	if (minimap->min_x < 0)
	{
		x_extent = 0 - minimap->min_x;
		minimap->min_x = 0;
	}
	minimap->max_x = (int)app->player.pos_x
		+ minimap->radius + x_extent;
	if (minimap->max_x > app->textures->map_w - 1)
	{
		if (x_extent == 0)
		{
			x_extent = app->textures->map_w - 1 - minimap->max_x;
			minimap->min_x += x_extent;
			if (minimap->min_x < 0)
				minimap->min_x = 0;
		}
		minimap->max_x = app->textures->map_w - 1;
	}
}

void	calc_y_range(t_app *app)
{
	t_minimap	*minimap;
	int			y_extent;

	minimap = &app->minimap;
	y_extent = 0;
	minimap->min_y = (int)app->player.pos_y - minimap->radius;
	if (minimap->min_y < 0)
	{
		y_extent = 0 - minimap->min_y;
		minimap->min_y = 0;
	}
	minimap->max_y = (int)app->player.pos_y
		+ minimap->radius + y_extent;
	if (minimap->max_y > app->textures->map_h - 1)
	{
		if (y_extent == 0)
		{
			y_extent = app->textures->map_h - 1 - minimap->max_y;
			minimap->min_y += y_extent;
			if (minimap->min_y < 0)
				minimap->min_y = 0;
		}
		minimap->max_y = app->textures->map_h - 1;
	}
}

int	get_minimap_color(t_app *app, int x, int y)
{
	if (app->map[y][x] == CH_WALL)
		return (0xafc3c4);
	else if (app->map[y][x] == CH_CLOSED_DOOR)
		return (0xd481bc);
	else if (app->map[y][x] == CH_OPEN_DOOR)
		return (0xe0a6d0);
	return (0xffffff);
}
