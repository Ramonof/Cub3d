/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:31:50 by mrolande          #+#    #+#             */
/*   Updated: 2022/07/02 01:31:50 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	parse_line(char *line, t_textures *textures, int *map)
{
	int	i;

	i = 0;
	*map = 0;
	while (line[i])
	{
		if (!in_set(line[i], MAP_SET))
			error_exit("Bad map");
		if (line[i] != ' ' && line[i] != 0)
			*map = 1;
		i++;
	}
	if (!(*map))
		return ;
	if (i > textures->map_w)
		textures->map_w = i;
}

void	check_end(char *line, int *code, int fd)
{
	while (*code)
	{
		*code = get_next_line(fd, &line, 0);
		parse_end(line);
		free(line);
	}
}

int	parse_start(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!in_set(line[i], " "))
		{
			if (!in_set(line[i], MAP_SET))
				error_exit("Bad map");
			else
				return (1);
		}
		i++;
	}
	return (0);
}

void	get_to_map(char *line, int *code, int fd, int *iter)
{
	parse_start(line);
	while (*code)
	{
		*code = get_next_line(fd, &line, 0);
		if (parse_start(line))
			break ;
		iter++;
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	if (*code == 0)
		error_exit("No map");
}

int	get_map_info(int fd, t_textures *textures, char *line, int *code)
{
	int	map;
	int	iter;

	map = 0;
	iter = 0;
	get_to_map(line, code, fd, &iter);
	parse_line(line, textures, &map);
	if (!map)
		error_exit("No map");
	free(line);
	textures->map_h = 2;
	while (*code)
	{
		*code = get_next_line(fd, &line, 0);
		parse_line(line, textures, &map);
		free(line);
		if (!map)
			break ;
		textures->map_h++;
	}
	check_end(line, code, fd);
	return (iter);
}
