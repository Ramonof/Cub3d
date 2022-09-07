/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:55:38 by etobias           #+#    #+#             */
/*   Updated: 2022/09/07 13:55:47 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_minimap_range(t_app *app);
static void	draw_minimap_frame(t_app *app);
static void	put_minimap_cell(t_app *app, int x, int y, int col);
static int	map_coords(t_minimap *minimap, double value, bool is_x);

void	draw_minimap(t_app *app)
{
	int			x;
	int			y;
	int			col;
	t_minimap	*minimap;

	minimap = &app->minimap;
	calc_minimap_range(app);
	draw_minimap_frame(app);
	y = minimap->min_y;
	while (y < minimap->max_y + 1)
	{
		x = minimap->min_x;
		while (x < minimap->max_x + 1)
		{
			col = get_minimap_color(app, x, y);
			minimap->map_x = map_coords(minimap, x, true);
			minimap->map_y = map_coords(minimap, y, false);
			put_minimap_cell(app, minimap->map_x, minimap->map_y, col);
			++x;
		}
		++y;
	}
	minimap->map_x = map_coords(minimap, app->player.pos_x, true);
	minimap->map_y = map_coords(minimap, app->player.pos_y, false);
	put_minimap_cell(app, minimap->map_x, minimap->map_y, 0x05fa91);
}

static void	calc_minimap_range(t_app *app)
{
	calc_x_range(app);
	calc_y_range(app);
}

static void	draw_minimap_frame(t_app *app)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < app->minimap.radius * 2 + 3)
		put_minimap_cell(app, x++, y, 0x3275a8);
	y = 1;
	while (y < app->minimap.radius * 2 + 2)
	{
		put_minimap_cell(app, 0, y, 0x3275a8);
		x = 1;
		while (x < app->minimap.radius * 2 + 2)
			put_minimap_cell(app, x++, y, 0xffffff);
		put_minimap_cell(app, app->minimap.radius * 2 + 2, y, 0x3275a8);
		++y;
	}
	x = 0;
	while (x < app->minimap.radius * 2 + 3)
		put_minimap_cell(app, x++, y, 0x3275a8);
}

static void	put_minimap_cell(t_app *app, int x, int y, int col)
{
	int	i;
	int	j;

	i = 0;
	while (i < app->minimap.scale)
	{
		j = 0;
		while (j < app->minimap.scale)
		{
			my_mlx_pixel_put(&app->img, x * app->minimap.scale + j,
				y * app->minimap.scale + i, col);
			++j;
		}
		++i;
	}
}

static int	map_coords(t_minimap *minimap, double value, bool is_x)
{
	double	fraction;
	int		new_max;

	if (is_x)
	{
		new_max = minimap->max_x - minimap->min_x + 1;
		fraction = (value - minimap->min_x) / (minimap->max_x - minimap->min_x);
	}
	else
	{
		new_max = minimap->max_y - minimap->min_y + 1;
		fraction = (value - minimap->min_y) / (minimap->max_y - minimap->min_y);
	}
	return ((new_max - 1) * fraction + 1);
}
