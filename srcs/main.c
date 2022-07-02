/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:11:55 by mrolande          #+#    #+#             */
/*   Updated: 2022/07/02 00:16:26 by etobias          ###   ########.fr       */
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

	init_app(&app);

	app.map = malloc(24 * sizeof(int *));
	for (int y = 0; y < 24; y++)
	{
		app.map[y] = malloc(24 * sizeof(int));
		for (int x = 0; x < 24; x++)
			app.map[y][x] = worldMap[y][x];
	}

	setup_controls(&app);
	
	render(&app);

	mlx_loop(app.mlx);
}

<<<<<<< HEAD
static void	setup_controls(t_app *app)
{
	mlx_key_hook(app->mlx_win, keyboard_input, app);
=======
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
>>>>>>> 320fea2d54877ef0310ff6159d7d83d0083a4da9
}

int	main(int argc, char **argv)
{
	t_textures	textures;

	if (argc || argv)
		argc = write(1, *argv, ft_strlen(*argv));
	ft_putendl_fd(" start", 1);

	/*mlx*/
	mlx_test();
	/**/

	/*parse*/
	init_textures(&textures);
	start_parse("test_map1.cub", &textures);
	print_textures_data(&textures);
	free_textures_data(&textures);
	/**/

	return (0);
}

static void	setup_controls(t_app *app)
{
	mlx_hook(app->mlx_win, 2, 1L<<0, keyboard_input, app);
	mlx_hook(app->mlx_win, 6, 1L<<6, mouse_move, app);
	mlx_hook(app->mlx_win, 17, 0L, close_app, app);
}
