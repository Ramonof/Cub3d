/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 18:21:38 by etobias           #+#    #+#             */
/*   Updated: 2022/07/27 20:06:45 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(t_app *app);
static void	set_player_rot(t_app *app, char side);
static void	load_textures(t_app *app);

void	init_app(t_app *app)
{
	app->mlx = mlx_init();
	app->mlx_win = mlx_new_window(app->mlx, WIDTH, HEIGHT, "Cub3D");
	app->img.img = mlx_new_image(app->mlx, WIDTH, HEIGHT);
	app->img.addr = mlx_get_data_addr(app->img.img, &app->img.bits_per_pixel,
			&app->img.line_length,
			&app->img.endian);
	app->prev_mouse_x = -1;
	app->map = app->textures->map;
	app->update = true;
	init_player(app);
	load_textures(app);
}

static void	init_player(t_app *app)
{
	int	x;
	int	y;

	y = 0;
	while (y < app->textures->map_h)
	{
		x = 0;
		while (x < app->textures->map_w)
		{
			if (app->map[y][x] == 'N' || app->map[y][x] == 'S'
				|| app->map[y][x] == 'E' || app->map[y][x] == 'W')
			{
				set_player_rot(app, app->map[y][x]);
				app->player.posX = x + 0.5;
				app->player.posY = y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
}

static void	set_player_rot(t_app *app, char side)
{
	if (side == 'N')
	{
		app->player.dirX = 0;
		app->player.dirY = -1;
	}
	else if (side == 'S')
	{
		app->player.dirX = 0;
		app->player.dirY = 1;
	}
	else if (side == 'E')
	{
		app->player.dirX = 1;
		app->player.dirY = 0;
	}
	else if (side == 'W')
	{
		app->player.dirX = -1;
		app->player.dirY = 0;
	}
	app->player.planeX = (-1 + 2 * (side == 'E' || side == 'W'))
		* app->player.dirY * 0.66;
	app->player.planeY = (-1 + 2 * (side == 'E' || side == 'W'))
		* app->player.dirX * 0.66;
}

static void	load_textures(t_app *app)
{
	t_textures	*textures;
	int			size;
	void		*p;

	textures = app->textures;
	size = textures->size;
	p = mlx_xpm_file_to_image(app->mlx, textures->no, &size, &size);
	textures->n_texture = mlx_get_data_addr(p, &size, &size, &size);
	p = mlx_xpm_file_to_image(app->mlx, textures->so, &size, &size);
	textures->s_texture = mlx_get_data_addr(p, &size, &size, &size);
	p = mlx_xpm_file_to_image(app->mlx, textures->ea, &size, &size);
	textures->e_texture = mlx_get_data_addr(p, &size, &size, &size);
	p = mlx_xpm_file_to_image(app->mlx, textures->we, &size, &size);
	textures->w_texture = mlx_get_data_addr(p, &size, &size, &size);
}
