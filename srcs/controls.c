/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:27 by etobias           #+#    #+#             */
/*   Updated: 2022/08/28 12:02:57 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement(t_app *app, int keycode);
static void	move_player(t_app *app, double x_dir, double y_dir);
static void	rotate_camera(t_app *app, int direction);

int	keyboard_input(int keycode, t_app *app)
{
	movement(app, keycode);
	if (keycode == ESC_KEY)
		close_app(app);
	if (keycode == 101)
	{
		int map_x = (int)(app->player.posX + app->player.dirX);
		int map_y = (int)(app->player.posY + app->player.dirY);
		if (app->map[map_y][map_x] == 'D')
		{
			app->map[map_y][map_x] = '3';
			app->update = true;
		}
		else if (app->map[map_y][map_x] == '3')
		{
			app->map[map_y][map_x] = 'D';
			app->update = true;
		}
	}
	return (0);
}

static void	movement(t_app *app, int keycode)
{
	if (keycode == D_KEY)
		move_player(app, app->player.planeX, app->player.planeY);
	else if (keycode == A_KEY)
		move_player(app, -app->player.planeX, -app->player.planeY);
	else if (keycode == W_KEY)
		move_player(app, app->player.dirX, app->player.dirY);
	else if (keycode == S_KEY)
		move_player(app, -app->player.dirX, -app->player.dirY);
}

static void	move_player(t_app *app, double x_dir, double y_dir)
{
	double	x_speed;
	double	y_speed;
	int		next_x;
	int		next_y;

	x_speed = x_dir * SPEED;
	y_speed = y_dir * SPEED;
	next_x = (int)(app->player.posX + x_speed);
	next_y = (int)(app->player.posY + y_speed);
	if (app->map[next_y][(int)app->player.posX] == '1'
		|| app->map[next_y][(int)app->player.posX] == 'D')
		y_speed = 0.0;
	if (app->map[(int)app->player.posY][next_x] == '1'
		|| app->map[(int)app->player.posY][next_x] == 'D')
		x_speed = 0.0;
	app->player.posX += x_speed;
	app->player.posY += y_speed;
	app->update = true;
}

int	mouse_move(int x, int y, t_app *app)
{
	y += 0;
	if (app->prev_mouse_x == -1)
		app->prev_mouse_x = x;
	if (app->prev_mouse_x > x)
		rotate_camera(app, -1);
	else if (app->prev_mouse_x < x)
		rotate_camera(app, 1);
	app->prev_mouse_x = x;
	return (0);
}

static void	rotate_camera(t_app *app, int direction)
{
	t_player	*p;
	double		rotation;
	double		temp_x;			

	rotation = ROT_SPEED * direction;
	p = &app->player;
	temp_x = p->dirX;
	p->dirX = p->dirX * cos(rotation) - p->dirY * sin(rotation);
	p->dirY = temp_x * sin(rotation) + p->dirY * cos(rotation);
	temp_x = p->planeX;
	p->planeX = p->planeX * cos(rotation) - p->planeY * sin(rotation);
	p->planeY = temp_x * sin(rotation) + p->planeY * cos(rotation);
	app->update = true;
}
