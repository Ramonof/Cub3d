/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:19 by etobias           #+#    #+#             */
/*   Updated: 2022/07/26 02:28:53 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_player *player, t_ray *ray, int screen_x);
static void	render_screen_line(t_app *app, t_ray *ray);
static void	get_line_borders(t_ray *ray, int side);
static int	cast_ray(t_app *app, t_ray *ray);

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
	int	side;
	int	text_size;

	text_size = app->textures->size;
	side = cast_ray(app, ray);
	get_line_borders(ray, side);
	
	double	perp_wall_dist;
	if (!(side % 2))
		perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	double	hit_x;
	if (!(side % 2))
		hit_x = app->player.posY + perp_wall_dist * ray->ray_dir_y;
	else
		hit_x = app->player.posX + perp_wall_dist * ray->ray_dir_x;
	hit_x -= floor(hit_x);
	
	int	tex_x = (int)(hit_x * (float)text_size);

	int	lineHeight = (int)(HEIGHT / perp_wall_dist);
	// How much to increase the texture coordinate per screen pixel
	double	step = 1.0 * (float)text_size / lineHeight;
	// Starting texture coordinate
	double	tex_pos = (ray->draw_start - HEIGHT / 2 + lineHeight / 2) * step;
	char	*texture;
	if (side == 0)
		texture = app->textures->n_texture;
	else if (side == 1)
		texture = app->textures->s_texture;
	else if (side == 2)
		texture = app->textures->e_texture;
	else if (side == 3)
		texture = app->textures->w_texture;
	else
		texture = app->textures->n_texture;

	int	y;
	y = ray->draw_start;
	while (y < ray->draw_end + 1)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int	texY = (int)tex_pos & (text_size - 1);
        tex_pos += step;

		unsigned int	ind = text_size * texY + tex_x;
		unsigned int	*p = (unsigned int *)texture;
		int				col = mlx_get_color_value(app->mlx, p[ind]);

		my_mlx_pixel_put(&app->img, ray->screen_x, y, col);
		++y;
	}

	int	screen_y;

	screen_y = 0;
	t_color	color = app->textures->c;
	int		c = create_argb(255, color.r, color.g, color.b);
	while (screen_y < ray->draw_start)
		my_mlx_pixel_put(&app->img, ray->screen_x, ++screen_y, c);
	screen_y = ray->draw_end;
	color = app->textures->f;
	c = create_argb(255, color.r, color.g, color.b);
	while (screen_y < HEIGHT)
		my_mlx_pixel_put(&app->img, ray->screen_x, ++screen_y, c);
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
	int		lineHeight;

	if (!(side % 2))
		perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	lineHeight = (int)(HEIGHT / perp_wall_dist);
	ray->draw_start = -lineHeight / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = lineHeight / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}
