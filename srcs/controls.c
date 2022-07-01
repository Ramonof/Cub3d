#include "cub3d.h"

int	keyboard_input(int keycode, t_app *app)
{
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
	else if (keycode == ESC_KEY)
	{
		mlx_destroy_window(app->mlx, app->mlx_win);
		exit(1);
	}
	app->player.posX = fclamp(app->player.posX, 0, 23);
	app->player.posY = fclamp(app->player.posY, 0, 23);
	render(app);
	return (0);
}

int mouse_move(int x, int y, t_app *app)
{
	double		temp_x;
	t_player	*p;

	y += 0;
	p = &app->player;
	if (app->prev_mouse_x == -1)
		app->prev_mouse_x = x;
	if (app->prev_mouse_x > x)
	{
		temp_x = p->dirX;
		p->dirX = p->dirX * cos(-ROT_SPEED) - p->dirY * sin(-ROT_SPEED);
		p->dirY = temp_x * sin(-ROT_SPEED) + p->dirY * cos(-ROT_SPEED);

		temp_x = p->planeX;
		p->planeX = p->planeX * cos(-ROT_SPEED) - p->planeY * sin(-ROT_SPEED);
		p->planeY = temp_x * sin(-ROT_SPEED) + p->planeY * cos(-ROT_SPEED);
	}
	else if (app->prev_mouse_x < x)
	{
		temp_x = p->dirX;
		p->dirX = p->dirX * cos(ROT_SPEED) - p->dirY * sin(ROT_SPEED);
		p->dirY = temp_x * sin(ROT_SPEED) + p->dirY * cos(ROT_SPEED);

		temp_x = p->planeX;
		p->planeX = p->planeX * cos(ROT_SPEED) - p->planeY * sin(ROT_SPEED);
		p->planeY = temp_x * sin(ROT_SPEED) + p->planeY * cos(ROT_SPEED);
	}
	app->prev_mouse_x = x;
	render(app);
	return (0);
}
