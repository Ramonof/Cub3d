/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:26:33 by etobias           #+#    #+#             */
/*   Updated: 2022/09/06 22:27:30 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_x_range(t_app *app)
{
	t_minimap	*minimap;

	minimap = &app->minimap;
	minimap->x_extent = 0;
	minimap->min_x = (int)app->player.posX - minimap->radius;
	if (minimap->min_x < 0)
	{
		minimap->x_extent = 0 - minimap->min_x;
		minimap->min_x = 0;
	}
	minimap->max_x = (int)app->player.posX
		+ minimap->radius + minimap->x_extent;
	if (minimap->max_x > app->textures->map_w - 1)
	{
		if (minimap->x_extent == 0)
		{
			minimap->x_extent = app->textures->map_w - 1 - minimap->max_x;
			minimap->min_x += minimap->x_extent;
			if (minimap->min_x < 0)
				minimap->min_x = 0;
		}
		minimap->max_x = app->textures->map_w - 1;
	}
}

void	calc_y_range(t_app *app)
{
	t_minimap	*minimap;

	minimap = &app->minimap;
	minimap->y_extent = 0;
	minimap->min_y = (int)app->player.posY - minimap->radius;
	if (minimap->min_y < 0)
	{
		minimap->y_extent = 0 - minimap->min_y;
		minimap->min_y = 0;
	}
	minimap->max_y = (int)app->player.posY
		+ minimap->radius + minimap->y_extent;
	if (minimap->max_y > app->textures->map_h - 1)
	{
		if (minimap->y_extent == 0)
		{
			minimap->y_extent = app->textures->map_h - 1 - minimap->max_y;
			minimap->min_y += minimap->y_extent;
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
