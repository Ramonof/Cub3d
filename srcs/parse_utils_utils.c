/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:22:37 by mrolande          #+#    #+#             */
/*   Updated: 2022/07/05 11:22:37 by mrolande         ###   ########.fr       */
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
	info->b = ft_atoi(line);
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
