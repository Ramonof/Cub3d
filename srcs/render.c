/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:19 by etobias           #+#    #+#             */
/*   Updated: 2022/07/27 21:02:25 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		init_ray(t_player *player, t_ray *ray, int screen_x);
static void		render_screen_line(t_app *app, t_ray *ray);
static void		get_line_borders(t_ray *ray, int side);
static char		*get_texture(t_textures *textures, int side);
static void		calc_ray_side_dist(t_player *player, t_ray *ray);
static int		cast_ray(t_app *app, t_ray *ray);
static int		get_text_x(t_app *app, t_ray *ray, int side, double wall_dist);
static double	get_wall_dist(t_ray *ray, int side);
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

static void	calc_ray_side_dist(t_player *player, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->posX - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->posX) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->posY - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->posY) * ray->delta_dist_y;
	}
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
	tex_x = get_text_x(app, ray, side, perp_wall_dist);
	line_height = (int)(HEIGHT / perp_wall_dist);
	// How much to increase the texture coordinate per screen pixel
	ray->step = 1.0 * (float)app->textures->size / line_height;
	// Starting texture coordinate
	ray->tex_pos = (ray->draw_start - HEIGHT / 2 + line_height / 2) * ray->step;
	texture = get_texture(app->textures, side);
	draw(app, ray, texture, tex_x);
}

static void	draw(t_app *app, t_ray *ray, char *texture, int tex_x)
{
	int				y;
	int				texY;
	unsigned int	ind;
	unsigned int	*p;
	int				col;

	y = ray->draw_start;
	while (y < ray->draw_end + 1)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		texY = (int)ray->tex_pos & (app->textures->size - 1);
		ray->tex_pos += ray->step;
		ind = app->textures->size * texY + tex_x;
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

static double	get_wall_dist(t_ray *ray, int side)
{
	if (!(side % 2))
		return (ray->side_dist_x - ray->delta_dist_x);
	return (ray->side_dist_y - ray->delta_dist_y);
}

static int	get_text_x(t_app *app, t_ray *ray, int side, double wall_dist)
{
	double	hit_x;
	int		tex_x;

	if (!(side % 2))
		hit_x = app->player.posY + wall_dist * ray->ray_dir_y;
	else
		hit_x = app->player.posX + wall_dist * ray->ray_dir_x;
	hit_x -= floor(hit_x);
	tex_x = (int)(hit_x * (float)app->textures->size);
	return (tex_x);
}

static char	*get_texture(t_textures *textures, int side)
{
	if (side == 0)
		return (textures->n_texture);
	else if (side == 1)
		return (textures->s_texture);
	else if (side == 2)
		return (textures->e_texture);
	else if (side == 3)
		return (textures->w_texture);
	else
		return (textures->n_texture);
}

static int	cast_ray(t_app *app, t_ray *ray)
{
	int	side;
	int	temp_x;
	int	temp_y;

	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			temp_x = ray->map_x;
			ray->map_x += ray->step_x;
			if (temp_x < ray->map_x)
				side = 0;
			else
				side = 2;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			temp_y = ray->map_y;
			ray->map_y += ray->step_y;
			if (temp_y < ray->map_y)
				side = 1;
			else
				side = 3;
		}
		if (app->map[ray->map_y][ray->map_x] == '1')
			return (side);
	}
	return (0);
}

static void	get_line_borders(t_ray *ray, int side)
{
	double	perp_wall_dist;
	int		line_height;

	if (!(side % 2))
		perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	line_height = (int)(HEIGHT / perp_wall_dist);
	ray->draw_start = -line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}
