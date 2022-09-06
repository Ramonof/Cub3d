/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:35 by etobias           #+#    #+#             */
/*   Updated: 2022/09/07 02:17:17 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

int	get_text_x(t_app *app, t_ray *ray, int side, double wall_dist)
{
	double	hit_x;
	int		tex_x;

	if (!(side % 2))
		hit_x = app->player.pos_y + wall_dist * ray->ray_dir_y;
	else
		hit_x = app->player.pos_x + wall_dist * ray->ray_dir_x;
	hit_x -= floor(hit_x);
	tex_x = (int)(hit_x * (float)app->textures->size);
	return (tex_x);
}

void	get_line_borders(t_ray *ray, int side)
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
