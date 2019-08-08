/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:17:33 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/05 15:17:37 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	w_error_map(int err_nb)
{
	if (err_nb == ERR_LENGTH)
	{
		ft_putendl("Size of your labyrinth is invalid");
		exit(err_nb);
	}
	else if (err_nb == ERR_HEIGHT)
	{
		ft_putendl("Size of your labyrinth is invalid");
		exit(err_nb);
	}
	else if (err_nb == ERR_WALL)
	{
		ft_putendl("Detected invalid symbol in the labyrinth perimeter");
		exit(err_nb);
	}
	else if (err_nb == ERR_FREE)
	{
		ft_putendl("There is no free place for a player in your labyrinth");
		exit(err_nb);
	}
	else if (err_nb == ERR_WRONG_SYMBOL)
	{
		ft_putendl("Detected invalid symbol in the labyrinth");
		exit(err_nb);
	}
}

void		w_error(int err_nb, int fd)
{
	if (fd != -42)
		close(fd);
	if (err_nb == ERR_USAGE)
	{
		ft_putendl("Usage : ./wolf3d <the labyrinth>");
		exit(err_nb);
	}
	else if (err_nb == ERR_MALLOC)
	{
		ft_putendl("Malloc failed");
		exit(err_nb);
	}
	else if (err_nb == ERR_SDL)
	{
		ft_putendl("SDL_function failed:");
		ft_putendl(SDL_GetError());
		exit(err_nb);
	}
	else if (err_nb == ERR_ARGV)
	{
		ft_putendl("Invalid argument or empty map");
		exit(err_nb);
	}
	w_error_map(err_nb);
}
