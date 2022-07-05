/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:42:13 by mrolande          #+#    #+#             */
/*   Updated: 2022/07/01 21:42:13 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_arrc(t_color *info, char *line)
{
	int		nbr;

	if (info->r != -1)
		error_exit("Double info");
	while (*line == ' ')
		line++;
	if (*line == 0 || !ft_isdigit(*line))
		error_exit("Empty info");
	nbr = 0;
	nbr = fill_r(info, line, nbr);
	nbr = fill_g(info, line, nbr);
	nbr = fill_b(info, line, nbr);
}

char	*fill_arr(char *info, char *line)
{
	char	*hold;
	int		len;

	while (*line == ' ')
		line++;
	fill_arr_util(info, line);
	hold = line;
	len = 0;
	while (*line)
	{
		len++;
		line++;
	}
	info = (char *)malloc(sizeof(char) * (len + 1));
	if (!info)
		error_exit("Malloc");
	while (*hold)
	{
		*info = *hold;
		hold++;
		info++;
	}
	*info = 0;
	info -= len;
	return (info);
}

void	info_type(char *line, t_textures *textures, int *code)
{
	while (*line == ' ')
		line++;
	if (*line == 0)
		return ;
	if (!ft_strncmp(line, "NO ", 3))
		textures->no = fill_arr(textures->no, line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		textures->so = fill_arr(textures->so, line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		textures->we = fill_arr(textures->we, line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		textures->ea = fill_arr(textures->ea, line + 3);
	else if (!ft_strncmp(line, "F ", 2))
		fill_arrc(&(textures->f), line + 2);
	else if (!ft_strncmp(line, "C ", 2))
		fill_arrc(&(textures->c), line + 2);
	else
		*code = *code * 2;
}

int	check_mapfile(char *map_name)
{
	int	fd;
	int	i;

	i = 0;
	while (map_name[i])
		i++;
	if (map_name[i - 1] != 'b' || map_name[i - 2] != 'u'
		|| map_name[i - 3] != 'c' || map_name[i - 4] != '.')
		error_exit("Bad map format");
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		errno_exit("Map file");
	return (fd);
}

void	start_parse(char *map_name, t_textures *textures)
{
	char	*line;
	int		fd;
	int		code;
	int		iter;

	code = 1;
	iter = 0;
	fd = check_mapfile(map_name);
	while (code == 1)
	{
		code = get_next_line(fd, &line, 0);
		info_type(line, textures, &code);
		iter++;
		if (code == 2)
			break ;
		free(line);
	}
	iter += get_map_info(fd, textures, line, &code);
	close(fd);
	fd = open(map_name, O_RDONLY);
	get_map(textures, iter, fd, line);
	close(fd);
}
