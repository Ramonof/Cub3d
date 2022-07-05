/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:14:06 by mrolande          #+#    #+#             */
/*   Updated: 2022/07/05 11:14:06 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	parse_end(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!in_set(line[i], " "))
			error_exit("Bad map");
		i++;
	}
}

void	fill_arr_util(char *info, char *line)
{
	if (info)
		error_exit("Double info");
	if (*line == 0)
		error_exit("Empty info");
}
