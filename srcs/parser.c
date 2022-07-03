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

int	my_atoi(char *str)
{
	long	nbr;
	long	sign;

	sign = 1;
	nbr = 0;
	while ((*str != '\0') && ('0' <= *str) && (*str <= '9'))
	{
		nbr = (nbr * 10) + (*str - '0');
		if (nbr > 2147483648 && sign == -1)
			return (0);
		if (nbr > 2147483647 && sign == 1)
			return (-1);
		str++;
	}
	return (sign * nbr);
}

void	valid_color(char *str, int num)
{
	int	len;

	len = 0;
	while ((*str != '\0') && ('0' <= *str) && (*str <= '9'))
	{
		len++;
		if (len > 3)
			error_exit("Bad color");
		str++;
	}
	if (num > 255 || num < 0)
		error_exit("Bad color");
}

int	fill_b(t_color *info, char *line, int nbr)
{
	line += nbr;
	info->b=ft_atoi(line);
	valid_color(line, info->b);
	while (ft_isdigit(*line))
	{
		line++;
		nbr++;
	}
	while (*line == ' ')
		line++;
	if (*line)
	 	error_exit("Incorrect info format");
	return (nbr);
}

int	fill_g(t_color *info, char *line, int nbr)
{
	line += nbr;
	info->g = ft_atoi(line);
	valid_color(line, info->g);
	while (ft_isdigit(*line))
	{
		line++;
		nbr++;
	}
	if (*line != ',')
	 	error_exit("Incorrect info format");
	line++;
	nbr++;
	while (*line == ' ')
	{
		line++;
		nbr++;
	}
	if (!ft_isdigit(*line))
	 	error_exit("Incorrect info format");
	return (nbr);
}

int	fill_r(t_color *info, char *line, int nbr)
{
	line += nbr;
	info->r = ft_atoi(line);
	valid_color(line, info->r);
	while (ft_isdigit(*line))
	{
		line++;
		nbr++;
	}
	if (*line != ',')
	 	error_exit("Incorrect info format");
	line++;
	nbr++;
	while (*line == ' ')
	{
		line++;
		nbr++;
	}
	if (!ft_isdigit(*line))
	 	error_exit("Incorrect info format");
	return (nbr);
}

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

	if (info)
		error_exit("Double info");
	while (*line == ' ')
		line++;
	if (*line == 0)
		error_exit("Empty info");
	hold = line;
	len = 0;
	while(*line)
	{
		len++;
		line++;
	}
	info = (char*)malloc(sizeof(char) * (len + 1));
	if (!info)
            error_exit("Malloc");
	while(*hold)
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
		textures->no = fill_arr(textures->no, line+3);
	else if (!ft_strncmp(line, "SO ", 3))
		textures->so = fill_arr(textures->so, line+3);
	else if (!ft_strncmp(line, "WE ", 3))
		textures->we = fill_arr(textures->we, line+3);
	else if (!ft_strncmp(line, "EA ", 3))
		textures->ea = fill_arr(textures->ea, line+3);
	else if (!ft_strncmp(line, "F ", 2))
		fill_arrc(&(textures->f), line+2);
	else if (!ft_strncmp(line, "C ", 2))
		fill_arrc(&(textures->c), line+2);
	else
		*code = *code * 2;
}

int	check_mapfile(char *map_name)
{
	int	fd, i;

	i = 0;
	while (map_name[i])
		i++;
	if (map_name[i-1] != 'b' || map_name[i-2] != 'u' || map_name[i-3] != 'c' ||
		map_name[i-4] != '.')
		error_exit("Bad map format");
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		errno_exit("Map file");
	return (fd);
}

void	start_parse(char *map_name, t_textures *textures)
{
	char	*line;
	int		fd, code, iter;

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
