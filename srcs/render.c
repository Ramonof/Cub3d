/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:19 by etobias           #+#    #+#             */
/*   Updated: 2022/09/07 02:17:17 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		init_ray(t_player *player, t_ray *ray, int screen_x);
static void		render_screen_line(t_app *app, t_ray *ray);
static void		draw(t_app *app, t_ray *ray, char *texture, int tex_x);
static void		draw_ceil_floor(t_app *app, t_ray *ray);

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
	draw_minimap(app);
	mlx_put_image_to_window(app->mlx, app->mlx_win, app->img.img, 0, 0);
}

static void	init_ray(t_player *player, t_ray *ray, int screen_x)
{
	double	camera_x;

	ray->screen_x = screen_x;
	camera_x = 2 * ray->screen_x / (double)WIDTH - 1;
	ray->ray_dir_x = player->dirX + player->planeX * camera_x;
	ray->ray_dir_y = player->dirY + player->planeY * camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
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
	texture = get_texture(app, ray, side);
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
	c = create_argb(0, color.r, color.g, color.b);
	while (screen_y < ray->draw_start)
		my_mlx_pixel_put(&app->img, ray->screen_x, screen_y++, c);
	screen_y = ray->draw_end + 1;
	color = app->textures->f;
	c = create_argb(0, color.r, color.g, color.b);
	while (screen_y < HEIGHT)
		my_mlx_pixel_put(&app->img, ray->screen_x, screen_y++, c);
}
