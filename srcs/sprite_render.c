/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 00:55:29 by etobias           #+#    #+#             */
/*   Updated: 2022/09/05 23:18:51 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_sprite_order(t_player *player, t_sprites *sprites_data);
static void	get_tex_x(t_sprites *spr_data, t_textures *textures);
static void	draw_sprite_stripe(t_app *app);
static void	put_sprite_pixel(t_app *app, int tex_y, int y);

void	draw_sprites(t_app *app)
{
	size_t		i;
	t_sprites	*spr_data;

	spr_data = &app->sprites_data;
	init_sprite_order(&app->player, spr_data);
	sort_sprites(spr_data);
	i = 0;
	while (i < spr_data->spr_count)
	{
		calc_sprite_data(&app->player, spr_data, i);
		calc_sprite_borders(spr_data);
		spr_data->stripe = spr_data->draw_start_x;
		while (spr_data->stripe < spr_data->draw_end_x)
		{
			get_tex_x(spr_data, app->textures);
			if (spr_data->transform_y > 0 && spr_data->stripe > 0
				&& spr_data->stripe < WIDTH
				&& spr_data->transform_y < app->z_buffer[spr_data->stripe])
				draw_sprite_stripe(app);
			++spr_data->stripe;
		}
		++i;
	}
	free(spr_data->spr_distance);
	free(spr_data->spr_order);
}

static void	init_sprite_order(t_player *player, t_sprites *spr_data)
{
	size_t	i;

	spr_data->spr_order = malloc(sizeof(int) * spr_data->spr_count);
	spr_data->spr_distance = malloc(sizeof(double) * spr_data->spr_count);
	i = 0;
	while (i < spr_data->spr_count)
	{
		spr_data->spr_order[i] = i;
		spr_data->spr_distance[i] = (player->posX - spr_data->sprites[i].x)
			* (player->posX - spr_data->sprites[i].x)
			+ (player->posY - spr_data->sprites[i].y)
			* (player->posY - spr_data->sprites[i].y);
		++i;
	}
}

static void	get_tex_x(t_sprites *spr_data, t_textures *textures)
{
	spr_data->tex_x = (int)((spr_data->stripe
				- (-spr_data->spr_width / 2 + spr_data->spr_screen_x))
			* textures->size / spr_data->spr_width);
}

static void	draw_sprite_stripe(t_app *app)
{
	int	y;
	int	d;
	int	tex_y;

	y = app->sprites_data.draw_start_y;
	while (y < app->sprites_data.draw_end_y)
	{
		d = y - HEIGHT / 2 + app->sprites_data.sprite_height / 2;
		tex_y = (d * app->textures->size) / app->sprites_data.sprite_height;
		put_sprite_pixel(app, tex_y, y);
		++y;
	}
}

static void	put_sprite_pixel(t_app *app, int tex_y, int y)
{
	unsigned int	ind;
	unsigned int	*p;
	int				col;

	ind = app->textures->size * tex_y + app->sprites_data.tex_x;
	p = (unsigned int *)app->textures->sprite_texture;
	col = mlx_get_color_value(app->mlx, p[ind]);
	if (col != 0)
		my_mlx_pixel_put(&app->img, app->sprites_data.stripe, y, col);
}
