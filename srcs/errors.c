/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 23:10:28 by mrolande          #+#    #+#             */
/*   Updated: 2022/07/01 23:10:28 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(char *err)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err, 2);
	exit(1);
}

void	errno_exit(char *err)
{
	perror(err);
	exit (errno);
}
