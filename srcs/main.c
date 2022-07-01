/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:11:55 by mrolande          #+#    #+#             */
/*   Updated: 2022/07/01 15:57:32 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_controls(t_app *app);

int worldMap[24][24]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,4,4,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

void	mlx_test(void)
{
	t_app	app;

	app.mlx = mlx_init();
	app.mlx_win = mlx_new_window(app.mlx, WIDTH, HEIGHT, "Hello world!");
	app.img.img = mlx_new_image(app.mlx, WIDTH, HEIGHT);
	app.img.addr = mlx_get_data_addr(app.img.img, &app.img.bits_per_pixel, &app.img.line_length,
								&app.img.endian);

	app.map = malloc(24 * sizeof(int *));
	for (int y = 0; y < 24; y++)
	{
		app.map[y] = malloc(24 * sizeof(int));
		for (int x = 0; x < 24; x++)
		{
			app.map[y][x] = worldMap[y][x];
		}
	}

	app.player.posY = 3.5;
	app.player.posX = 22.5;
	app.player.dirX = -1;
	app.player.dirY = 0;
	app.player.planeX = 0;
	app.player.planeY = -0.66;

	app.prev_mouse_x = -1;
	
	render(&app);

	setup_controls(&app);

	mlx_loop(app.mlx);
}

static void	setup_controls(t_app *app)
{
	mlx_hook(app->mlx_win, 2, 1L<<0, keyboard_input, app);
	mlx_hook(app->mlx_win, 6, 1L<<6, mouse_move, app);
}

void	gnl_test(void)
{
	int		fd, code = 1, hld;
	char	*line;

	fd = open("README.md", O_RDONLY);
	while (code)
	{
		code = get_next_line(fd, &line, 0);
		if (*line)
		{
			hld = write(1, line, ft_strlen(line));
			hld = write(1, "\n", 1);
		}
		free(line);
	}
	close(fd);
	hld--;
}

int	main(int argc, char **argv)
{
	if (argc || argv)
		argc = write(1, *argv, ft_strlen(*argv));
	gnl_test();
	mlx_test();
	return (0);
}