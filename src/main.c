/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:23:26 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/21 19:36:30 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	load_image(t_wolf *wolf)
{
	int i;

	i = -1;
	BMP[0] = IMG_Load("./img/bricks.bmp");
	BMP[1] = IMG_Load("./img/lavaf4.bmp");
	BMP[2] = IMG_Load("./img/leavesop.bmp");
	BMP[3] = IMG_Load("./img/walkstone.bmp");
	BMP[4] = IMG_Load("./img/bluestone.bmp");
	BMP[5] = IMG_Load("./img/redbrick.bmp");
	BMP[6] = IMG_Load("./img/wood.bmp");
	BMP[7] = IMG_Load("./img/eagle.bmp");
	while (++i < 8)
	{
		if (!(BMP[i]))
			w_error(ERR_SDL, wolf->fd);
	}
}

static void	init_wolf(t_wolf *wolf)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		w_error(ERR_SDL, wolf->fd);
	WIN = SDL_CreateWindow("Wolf3d",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WDTH, HGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	if (!WIN)
		w_error(ERR_SDL, wolf->fd);
	SURF_WIN = SDL_GetWindowSurface(WIN);
	if (!SURF_WIN)
		w_error(ERR_SDL, wolf->fd);
	BMP = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 8);
	if (!BMP)
		w_error(ERR_MALLOC, wolf->fd);
	load_image(wolf);
}

static void	init_param(t_wolf *wolf)
{
	S_FREE = ' ';
	S_WALL = '*';
	S_PLYR = '+';
	FLAGS.free_sp = 0;
	FLAGS.player = 0;
	LBRNT.rays = WDTH;
	FLAGS.textur = 0;
	FLAGS.speed = 1;
	FLAGS.zoom = 1.0;
	LBRNT.ply_drct_x = -1;
	LBRNT.ply_drct_y = 0;
	LBRNT.prjct_x = 0;
	LBRNT.prjct_y = 0.60;
}

static void	valid_name(char *name, int fd)
{
	int len;

	len = ft_strlen(name);
	if (len < 5)
		w_error(ERR_ARGV, fd);
	if (ft_strcmp(".map", &name[len - 4]) != 0)
		w_error(ERR_ARGV, fd);
}

int			main(int ac, char **av)
{
	t_wolf	*wolf;

	if (ac != 2)
		w_error(ERR_USAGE, -42);
	wolf = (t_wolf *)malloc(sizeof(t_wolf));
	if (!wolf)
		w_error(ERR_MALLOC, -42);
	wolf->fd = -42;
	init_param(wolf);
	valid_name(av[1], wolf->fd);
	wolf->fd = open(av[1], O_RDONLY);
	w_valid_map(wolf, wolf->fd);
	close(wolf->fd);
	wolf->fd = -42;
	init_wolf(wolf);
	w_raycasting(wolf);
	w_event(wolf);
	return (0);
}
