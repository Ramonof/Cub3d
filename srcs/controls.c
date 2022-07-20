/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:27 by etobias           #+#    #+#             */
/*   Updated: 2022/07/20 18:21:27 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement(t_app *app, int keycode);
static void	rotate_camera(t_app *app, int direction);

int	keyboard_input(int keycode, t_app *app)
{
	movement(app, keycode);
	if (keycode == ESC_KEY)
		close_app(app);
	app->player.posX = fclamp(app->player.posX, 0, app->textures->map_w);
	app->player.posY = fclamp(app->player.posY, 0, app->textures->map_h);
	render(app);
	return (0);
}

static void	movement(t_app *app, int keycode)
{
	double X = app->player.posX;
	double Y = app->player.posY;

	if (keycode == D_KEY)
	{
		app->player.posX += app->player.planeX * SPEED;
		app->player.posY += app->player.planeY * SPEED;
	}
	else if (keycode == A_KEY)
	{
		app->player.posX -= app->player.planeX * SPEED;
		app->player.posY -= app->player.planeY * SPEED;
	}
	else if (keycode == W_KEY)
	{
		app->player.posX += app->player.dirX * SPEED;
		app->player.posY += app->player.dirY * SPEED;
	}
	else if (keycode == S_KEY)
	{
		app->player.posX -= app->player.dirX * SPEED;
		app->player.posY -= app->player.dirY * SPEED;
	}

	if (app->map[(int)app->player.posY][(int)app->player.posX] == '1')
	{
		app->player.posX = X;
		app->player.posY = Y;
	}
}

int mouse_move(int x, int y, t_app *app)
{
	y += 0;
	if (app->prev_mouse_x == -1)
		app->prev_mouse_x = x;
	if (app->prev_mouse_x > x)
		rotate_camera(app, -1);
	else if (app->prev_mouse_x < x)
		rotate_camera(app, 1);
	app->prev_mouse_x = x;
	render(app);
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
}
