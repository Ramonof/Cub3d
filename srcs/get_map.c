/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 12:03:30 by mrolande          #+#    #+#             */
/*   Updated: 2022/07/02 12:03:30 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	alloc_map(t_textures *textures)
{
	int	i;

	i = 0;
	textures->map = (char **)malloc(sizeof(char *) * (textures->map_h + 1));
	if (!textures->map)
		error_exit("Malloc");
	while (i < textures->map_h)
	{
		textures->map[i] = (char *)malloc(sizeof(char) * (textures->map_w + 1));
		if (!textures->map[i])
			error_exit("Malloc");
		i++;
	}
}

void	fill_line(t_textures *textures, char *line, int num)
{
	int	i;

	i = 0;
	while (line[i])
	{
		textures->map[num][i] = line[i];
		i++;
	}
	while (i < textures->map_w)
	{
		textures->map[num][i] = ' ';
		i++;
	}
	textures->map[num][i] = 0;
}

void	save_map(t_textures *textures, int fd, char *line)
{
	int	code;
	int	num;

	code = 1;
	num = 0;
	while (code == 1)
	{
		code = get_next_line(fd, &line, 0);
		fill_line(textures, line, num);
		free(line);
		num++;
		if (num == textures->map_h)
			break ;
	}
	textures->map[num] = 0;
}

void	get_map(t_textures *textures, int iter, int fd, char *line)
{
	int	code;
	int	cur_iter;

	code = 1;
	cur_iter = 0;
	while (code == 1)
	{
		code = get_next_line(fd, &line, 0);
		cur_iter++;
		free(line);
		if (cur_iter == iter - 1)
			break ;
	}
	alloc_map(textures);
	save_map(textures, fd, line);
	check_map(textures);
}
