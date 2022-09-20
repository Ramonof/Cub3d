/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 23:27:08 by etobias           #+#    #+#             */
/*   Updated: 2022/09/07 02:17:17 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_interaction(t_app *app)
{
	int	map_x;
	int	map_y;

	map_x = (int)(app->player.pos_x + app->player.dirx);
	map_y = (int)(app->player.pos_y + app->player.diry);
	if (app->map[map_y][map_x] == CH_CLOSED_DOOR)
	{
		app->map[map_y][map_x] = CH_OPEN_DOOR;
		app->update = true;
	}
	else if (app->map[map_y][map_x] == CH_OPEN_DOOR)
	{
		app->map[map_y][map_x] = CH_CLOSED_DOOR;
		app->update = true;
	}
}

void	move_player(t_app *app, double x_dir, double y_dir)
{
	double	x_speed;
	double	y_speed;
	int		next_x;
	int		next_y;

	x_speed = x_dir * SPEED;
	y_speed = y_dir * SPEED;
	next_x = (int)(app->player.pos_x + x_speed);
	next_y = (int)(app->player.pos_y + y_speed);
	if (app->map[next_y][(int)app->player.pos_x] == CH_WALL
		|| app->map[next_y][(int)app->player.pos_x] == CH_CLOSED_DOOR)
		y_speed = 0.0;
	if (app->map[(int)app->player.pos_y][next_x] == CH_WALL
		|| app->map[(int)app->player.pos_y][next_x] == CH_CLOSED_DOOR)
		x_speed = 0.0;
	app->player.pos_x += x_speed;
	app->player.pos_y += y_speed;
	app->update = true;
}

void	rotate_camera(t_app *app, int direction)
{
	t_player	*p;
	double		rotation;
	double		temp_x;			

	rotation = ROT_SPEED * direction;
	p = &app->player;
	temp_x = p->dirx;
	p->dirx = p->dirx * cos(rotation) - p->diry * sin(rotation);
	p->diry = temp_x * sin(rotation) + p->diry * cos(rotation);
	temp_x = p->planex;
	p->planex = p->planex * cos(rotation) - p->planey * sin(rotation);
	p->planey = temp_x * sin(rotation) + p->planey * cos(rotation);
	app->update = true;
}
