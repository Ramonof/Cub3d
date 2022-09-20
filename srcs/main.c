/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:11:55 by mrolande          #+#    #+#             */
/*   Updated: 2022/09/07 01:30:24 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_controls(t_app *app);

static int	main_loop(t_app *app)
{
	if (app->update)
	{
		render(app);
		app->update = false;
	}
	return (1);
}

void	start_game(t_app *app)
{
	init_app(app);
	setup_controls(app);
	mlx_loop_hook(app->mlx, main_loop, app);
	mlx_loop(app->mlx);
}

static void	setup_controls(t_app *app)
{
	mlx_hook(app->mlx_win, 2, 1L << 0, keyboard_input, app);
	mlx_hook(app->mlx_win, 6, 1L << 6, mouse_move, app);
	mlx_hook(app->mlx_win, 17, 0L, close_app, app);
}

int	main(int argc, char **argv)
{
	t_app		app;
	t_textures	textures;

	if (argc != 2)
		error_exit("Bad arguments");
	init_textures(&textures);
	start_parse(argv[1], &textures);
	app.textures = &textures;
	app.textures->size = 64;
	start_game(&app);
	free_memory(&app);
	return (0);
}
