/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 12:02:03 by mrolande          #+#    #+#             */
/*   Updated: 2022/07/03 12:02:03 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_enclosed_d(t_textures *textures, int i, int j)
{
	if (i != 0)
	{
		if (j != 0)
			if (textures->map[i - 1][j - j] == ' ')
				error_exit("Bad map : Map should be surrounded by walls");
		if (j != textures->map_w - 1)
			if (textures->map[i - 1][j + 1] == ' ')
				error_exit("Bad map : Map should be surrounded by walls");
	}
	if (i != textures->map_h - 1)
	{
		if (j != 0)
			if (textures->map[i + 1][j - 1] == ' ')
				error_exit("Bad map : Map should be surrounded by walls");
		if (j != textures->map_w - 1)
			if (textures->map[i + 1][j + 1] == ' ')
				error_exit("Bad map : Map should be surrounded by walls");
	}
}

void	check_enclosed_vh(t_textures *textures, int i, int j)
{
	if (textures->map[i][j] == '1' || textures->map[i][j] == ' ')
		return ;
	if (i != 0)
		if (textures->map[i - 1][j] == ' ')
			error_exit("Bad map : Map should be surrounded by walls");
	if (i != textures->map_h - 1)
		if (textures->map[i + 1][j] == ' ')
			error_exit("Bad map : Map should be surrounded by walls");
	if (j != 0)
		if (textures->map[i][j - 1] == ' ')
			error_exit("Bad map : Map should be surrounded by walls");
	if (j != textures->map_w - 1)
		if (textures->map[i][j + 1] == ' ')
			error_exit("Bad map : Map should be surrounded by walls");
	check_enclosed_d(textures, i, j);
}

void	check_border(t_textures *textures, int i, int j)
{
	if (i == 0)
		if (textures->map[i][j] != '1' && textures->map[i][j] != ' ')
			error_exit("Bad map : Map should be surrounded by walls");
	if (i == textures->map_h - 1)
		if (textures->map[i][j] != '1' && textures->map[i][j] != ' ')
			error_exit("Bad map : Map should be surrounded by walls");
	if (j == 0)
		if (textures->map[i][j] != '1' && textures->map[i][j] != ' ')
			error_exit("Bad map : Map should be surrounded by walls");
	if (j == textures->map_w - 1)
		if (textures->map[i][j] != '1' && textures->map[i][j] != ' ')
			error_exit("Bad map : Map should be surrounded by walls");
}

void	check_map(t_textures *textures)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (textures->map[i])
	{
		j = 0;
		while (textures->map[i][j])
		{
			if (in_set(textures->map[i][j], "NSEW"))
				player += 1;
			check_border(textures, i, j);
			check_enclosed_vh(textures, i, j);
			j++;
		}
		i++;
	}
	if (player != 1)
		error_exit("Bad starting position");
}
