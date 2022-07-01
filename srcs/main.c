/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etobias <etobias@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:11:55 by mrolande          #+#    #+#             */
/*   Updated: 2022/07/01 12:52:23 by etobias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	mlx_test(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Hello world!");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++)
			my_mlx_pixel_put(&img, j, i, 0x00FF0000);
	}

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
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