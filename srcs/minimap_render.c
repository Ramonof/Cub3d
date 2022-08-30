#include "cub3d.h"

static void calc_minimap_range(t_app *app);
static void	draw_minimap_frame(t_app *app);
static void	put_minimap_cell(t_app *app, int x, int y, int col);

void	draw_minimap(t_app *app)
{
	int	x;
	int	y;
	t_minimap   *minimap;
	
	minimap = &app->minimap;
	calc_minimap_range(app);
	draw_minimap_frame(app);
	y = minimap->min_y;
	while (y < minimap->max_y + 1)
	{
		x = minimap->min_x;
		while (x < minimap->max_x + 1)
		{
			int col = 0xfad987;
			if (app->map[y][x] == CH_WALL)
				col = 0xafc3c4;
			else if (app->map[y][x] == CH_CLOSED_DOOR)
				col = 0xd481bc;
			else if (app->map[y][x] == CH_OPEN_DOOR)
				col = 0xe0a6d0;
			int	map_x = map(minimap->min_x, minimap->max_x, 1, minimap->max_x - minimap->min_x + 1, x);
			int	map_y = map(minimap->min_y, minimap->max_y, 1, minimap->max_y - minimap->min_y + 1, y);
			put_minimap_cell(app, map_x, map_y, col);
			++x;
		}
		++y;
	}
	int	map_x = map(minimap->min_x, minimap->max_x, 1, minimap->max_x - minimap->min_x + 1, app->player.posX);
	int	map_y = map(minimap->min_y, minimap->max_y, 1, minimap->max_y - minimap->min_y + 1, app->player.posY);
	put_minimap_cell(app, map_x, map_y, 0x05fa91);
}

static void calc_minimap_range(t_app *app)
{
	int			x_extent;
	int			y_extent;
	t_minimap   *minimap;
	
	minimap = &app->minimap;
	x_extent = 0;
	minimap->min_x = app->player.posX - minimap->radius;
	if (minimap->min_x < 0)
	{
		x_extent = -minimap->min_x;
		minimap->min_x = 0;
	}
	y_extent = 0;
	minimap->min_y = app->player.posY - minimap->radius;
	if (minimap->min_y < 0)
	{
		y_extent = -minimap->min_y;
		minimap->min_y = 0;
	}
	minimap->max_x = app->player.posX + minimap->radius + x_extent;
	if (minimap->max_x > app->textures->map_w - 1)
	{
		if (x_extent == 0)
		{
			x_extent = app->textures->map_w - minimap->max_x;
			minimap->min_x += x_extent;
			if (minimap->min_x < 0)
				minimap->min_x = 0;
		}
		minimap->max_x = app->textures->map_w - 1;
	}
	minimap->max_y = app->player.posY + minimap->radius + y_extent;
	if (minimap->max_y > app->textures->map_h - 1)
	{
		if (y_extent == 0)
		{
			y_extent = app->textures->map_h - minimap->max_y;
			minimap->min_y += y_extent;
			if (minimap->min_y < 0)
				minimap->min_y = 0;
		}
		minimap->max_y = app->textures->map_h - 1;
	}
}

static void	draw_minimap_frame(t_app *app)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < app->minimap.radius * 2 + 2)
		put_minimap_cell(app, x++, y, 0x3275a8);
	y = 1;
	while (y < app->minimap.radius * 2)
	{
		put_minimap_cell(app, 0, y, 0x3275a8);
		put_minimap_cell(app, app->minimap.radius * 2 + 1, y, 0x3275a8);
		++y;
	}
	x = 0;
	while (x < app->minimap.radius * 2 + 2)
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
			my_mlx_pixel_put(&app->img, x * app->minimap.scale + j, y * app->minimap.scale + i, col);
			++j;
		}
		++i;
	}
}
