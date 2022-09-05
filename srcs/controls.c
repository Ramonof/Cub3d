/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:27 by etobias           #+#    #+#             */
/*   Updated: 2022/09/05 23:26:47 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement(t_app *app, int keycode);
static void	key_rotation(t_app *app, int keycode);

int	keyboard_input(int keycode, t_app *app)
{
	movement(app, keycode);
	key_rotation(app, keycode);
	if (keycode == ESC_KEY)
		close_app(app);
	if (keycode == E_KEY)
		door_interaction(app);
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

static void	key_rotation(t_app *app, int keycode)
{
	if (keycode == KEY_LEFT)
		rotate_camera(app, -1);
	else if (keycode == KEY_RIGHT)
		rotate_camera(app, 1);
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
