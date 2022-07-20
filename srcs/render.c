/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:19 by etobias           #+#    #+#             */
/*   Updated: 2022/07/20 18:48:43 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_player *player, t_ray *ray, int screen_x);
static void	render_screen_line(t_app *app, t_ray *ray);
static void	get_line_borders(t_ray *ray, int side);
static int	cast_ray(t_app *app, t_ray *ray);
static int	get_side_color(int side);
static void	draw_screen_line(t_data *img, t_ray *ray, int color);

void render(t_app *app)
{
	t_ray ray;

	for (int screen_x = 0; screen_x < WIDTH; screen_x++)
	{
		init_ray(&app->player, &ray, screen_x);
		
		render_screen_line(app, &ray);
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
	int side;
	
	side = cast_ray(app, ray);	

	get_line_borders(ray, side);

	int color = get_side_color(side);

	draw_screen_line(&app->img, ray, color);
}

static int	cast_ray(t_app *app, t_ray *ray)
{
	int	side;
	int	temp_x;
	int temp_y;
	
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
	double	perpWallDist;
	int		lineHeight;

	if (!(side % 2))
		perpWallDist = (ray->side_dist_x - ray->delta_dist_x);
	else
		perpWallDist = (ray->side_dist_y - ray->delta_dist_y);
	
	lineHeight = (int)(HEIGHT / perpWallDist);
	ray->draw_start = -lineHeight / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = lineHeight / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

static int get_side_color(int side)
{
	if (side == 0)
		return (0x03fcad);
	if (side == 1)
		return (0xfcce03);
	if (side == 2)
		return (0xfc5a03);
	if (side == 3)
		return (0xa0de66);
	return (0x0);
}

static void draw_screen_line(t_data *img, t_ray *ray, int color)
{
	int screen_y;

	screen_y = 0;
	while (screen_y < ray->draw_start)
		my_mlx_pixel_put(img, ray->screen_x, ++screen_y, CEILING_COLOR);
	while (screen_y < ray->draw_end)
		my_mlx_pixel_put(img, ray->screen_x, ++screen_y, color);
	while (screen_y < HEIGHT)
		my_mlx_pixel_put(img, ray->screen_x, ++screen_y, FLOOR_COLOR);
}
