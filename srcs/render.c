/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:19 by etobias           #+#    #+#             */
/*   Updated: 2022/08/24 01:26:32 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		init_ray(t_player *player, t_ray *ray, int screen_x);
static void		render_screen_line(t_app *app, t_ray *ray);
static void		draw(t_app *app, t_ray *ray, char *texture, int tex_x);
static void		draw_ceil_floor(t_app *app, t_ray *ray);

static void		draw_sprites(t_app *app)
{
	double sprite_x = app->sprites[0].x - app->player.posX;
	double sprite_y = app->sprites[0].y - app->player.posY;

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
		//the conditions in the if are:
		//1) it's in front of camera plane so you don't see things behind you
		//2) it's on the screen (left)
		//3) it's on the screen (right)
		//4) ZBuffer, with perpendicular distance
		if (transform_y > 0 && stripe > 0 && stripe < WIDTH && transform_y < app->z_buffer[stripe])
		{
			for (int y = draw_start_y; y < draw_end_y; y++) //for every pixel of the current stripe
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

void	render(t_app *app)
{
	t_ray	ray;
	int		screen_x;

	screen_x = 0;
	while (screen_x < WIDTH)
	{
		init_ray(&app->player, &ray, screen_x);
		render_screen_line(app, &ray);
		++screen_x;
	}
	draw_sprites(app);
	mlx_put_image_to_window(app->mlx, app->mlx_win, app->img.img, 0, 0);
}

static void	init_ray(t_player *player, t_ray *ray, int screen_x)
{
	double	camera_x;

	ray->screen_x = screen_x;
	camera_x = 2 * ray->screen_x / (double)WIDTH - 1;
	ray->ray_dir_x = player->dirX + player->planeX * camera_x;
	ray->ray_dir_y = player->dirY + player->planeY * camera_x;
	ray->map_x = (int)player->posX;
	ray->map_y = (int)player->posY;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = INFINITY;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = INFINITY;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	calc_ray_side_dist(player, ray);
}

static void	render_screen_line(t_app *app, t_ray *ray)
{
	int		side;
	double	perp_wall_dist;
	int		tex_x;
	int		line_height;
	char	*texture;

	side = cast_ray(app, ray);
	get_line_borders(ray, side);
	perp_wall_dist = get_wall_dist(ray, side);
	app->z_buffer[ray->screen_x] = perp_wall_dist;
	tex_x = get_text_x(app, ray, side, perp_wall_dist);
	line_height = (int)(HEIGHT / perp_wall_dist);
	ray->step = 1.0 * (float)app->textures->size / line_height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2 + line_height / 2) * ray->step;
	texture = get_texture(app->textures, side);
	draw(app, ray, texture, tex_x);
}

static void	draw(t_app *app, t_ray *ray, char *texture, int tex_x)
{
	int				y;
	int				tex_y;
	unsigned int	ind;
	unsigned int	*p;
	int				col;

	y = ray->draw_start;
	while (y < ray->draw_end + 1)
	{
		tex_y = (int)ray->tex_pos & (app->textures->size - 1);
		ray->tex_pos += ray->step;
		ind = app->textures->size * tex_y + tex_x;
		p = (unsigned int *)texture;
		col = mlx_get_color_value(app->mlx, p[ind]);
		my_mlx_pixel_put(&app->img, ray->screen_x, y, col);
		++y;
	}
	draw_ceil_floor(app, ray);
}

static void	draw_ceil_floor(t_app *app, t_ray *ray)
{
	int		screen_y;
	int		c;
	t_color	color;

	screen_y = 0;
	color = app->textures->c;
	c = create_argb(255, color.r, color.g, color.b);
	while (screen_y < ray->draw_start)
		my_mlx_pixel_put(&app->img, ray->screen_x, ++screen_y, c);
	screen_y = ray->draw_end + 1;
	color = app->textures->f;
	c = create_argb(255, color.r, color.g, color.b);
	while (screen_y < HEIGHT)
		my_mlx_pixel_put(&app->img, ray->screen_x, ++screen_y, c);
}
