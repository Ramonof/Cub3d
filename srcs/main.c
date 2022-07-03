/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:11:55 by mrolande          #+#    #+#             */
/*   Updated: 2022/07/02 14:50:11 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_controls(t_app *app);

void	mlx_test(t_app *app)
{
	init_app(app);

	setup_controls(app);
	
	render(app);

	mlx_loop(app->mlx);
}

static void	setup_controls(t_app *app)
{
	mlx_hook(app->mlx_win, 2, 1L<<0, keyboard_input, app);
	mlx_hook(app->mlx_win, 6, 1L<<6, mouse_move, app);
	mlx_hook(app->mlx_win, 17, 0L, close_app, app);
}

int	main(int argc, char **argv)
{
	t_app		app;
	t_textures	textures;

	if (argc != 2)
		error_exit("Bad arguments");

	/* parse */
	init_textures(&textures);
	start_parse(argv[1], &textures);
	print_textures_data(&textures);

	app.textures = &textures;

	/* mlx */
	mlx_test(&app);
	
	free_textures_data(&textures);

	return (0);
}
