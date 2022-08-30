#include "cub3d.h"

static void sort_sprites(int *sprite_order, double *sprite_distance, size_t sprite_count);

void    draw_sprites(t_app *app)
{
	int *sprite_order = malloc(app->sprite_count);
	double *sprite_distance = malloc(app->sprite_count);

	for (size_t i = 0; i < app->sprite_count; i++)
	{
		sprite_order[i] = i;
		sprite_distance[i] = (app->player.posX - app->sprites[i].x) * (app->player.posX - app->sprites[i].x)
			+ (app->player.posY - app->sprites[i].y) * (app->player.posY - app->sprites[i].y);
	}
	sort_sprites(sprite_order, sprite_distance, app->sprite_count);

	for (size_t i = 0; i < app->sprite_count; i++)
	{
		double sprite_x = app->sprites[sprite_order[i]].x - app->player.posX;
		double sprite_y = app->sprites[sprite_order[i]].y - app->player.posY;

		double inv_det = 1.0 / (app->player.planeX * app->player.dirY - app->player.planeY * app->player.dirX);
		
		double transform_x = inv_det * (app->player.dirY * sprite_x - app->player.dirX * sprite_y);
		double transform_y = inv_det * (-app->player.planeY * sprite_x + app->player.planeX * sprite_y);

		int sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));

		int sprite_height = abs((int)(HEIGHT / transform_y));

		int draw_start_y = -sprite_height / 2 + HEIGHT / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		
		int draw_end_y = sprite_height / 2 + HEIGHT / 2;
		if (draw_end_y >= HEIGHT)
			draw_end_y = HEIGHT - 1;

		int sprite_width = abs((int)(HEIGHT / transform_y));
		int draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;

		int draw_end_x = sprite_width / 2 + sprite_screen_x;
		if (draw_end_x >= WIDTH)
			draw_end_x = WIDTH - 1;

		for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
		{
			int tex_x = (int)((stripe - (-sprite_width / 2 + sprite_screen_x)) * app->textures->size / sprite_width);
			if (transform_y > 0 && stripe > 0 && stripe < WIDTH && transform_y < app->z_buffer[stripe])
			{
				for (int y = draw_start_y; y < draw_end_y; y++)
				{
					int d = y - HEIGHT / 2 + sprite_height / 2;
					int tex_y = (d * app->textures->size) / sprite_height;
					unsigned int ind = app->textures->size * tex_y + tex_x;
					unsigned int *p = (unsigned int *)app->textures->sprite_texture;
					int col = mlx_get_color_value(app->mlx, p[ind]);
					if (col != 0)
						my_mlx_pixel_put(&app->img, stripe, y, col);
				}
			}
		}
	}
}

static void		sort_sprites(int *sprite_order, double *sprite_distance, size_t sprite_count)
{
	size_t	i;

	i = 1;
	while (i < sprite_count)
	{
		if (sprite_distance[sprite_order[i - 1]] < sprite_distance[sprite_order[i]])
		{
			int temp = sprite_order[i - 1];
			sprite_order[i - 1] = sprite_order[i];
			sprite_order[i] = temp;
			i = 0;
		}
		++i;
	}
}
