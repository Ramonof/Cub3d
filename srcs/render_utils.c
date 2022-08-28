/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:30:54 by etobias           #+#    #+#             */
/*   Updated: 2022/08/28 11:48:04 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	calc_ray_pos(t_ray *ray);

double	get_wall_dist(t_ray *ray, int side)
{
	if (!(side % 2))
		return (ray->side_dist_x - ray->delta_dist_x);
	return (ray->side_dist_y - ray->delta_dist_y);
}

char	*get_texture(t_textures *textures, int side)
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

int	cast_ray(t_app *app, t_ray *ray)
{
	int	side;

	while (1)
	{
		side = calc_ray_pos(ray);
		if (app->map[ray->map_y][ray->map_x] == '1')
			return (side);
		if (app->map[ray->map_y][ray->map_x] == '2')
			return (side);
	}
	return (0);
}

static int	calc_ray_pos(t_ray *ray)
{
	int	temp_x;
	int	temp_y;

	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		temp_x = ray->map_x;
		ray->map_x += ray->step_x;
		if (temp_x < ray->map_x)
			return (0);
		else
			return (2);
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		temp_y = ray->map_y;
		ray->map_y += ray->step_y;
		if (temp_y < ray->map_y)
			return (1);
		else
			return (3);
	}
	return (0);
}

void	calc_ray_side_dist(t_player *player, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->posX - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->posX)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->posY - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->posY)
			* ray->delta_dist_y;
	}
}
