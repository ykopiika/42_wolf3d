/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_event.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:24:56 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/21 18:25:02 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	set_flags(t_wolf *wolf, int key)
{
	int flag;

	flag = (EVENT.type == SDL_KEYDOWN) ? 1 : 0;
	if (key == SDLK_a)
		FLAGS.keydown_a = flag;
	if (key == SDLK_d)
		FLAGS.keydown_d = flag;
	if (key == SDLK_UP)
		FLAGS.keydown_up = flag;
	if (key == SDLK_DOWN)
		FLAGS.keydown_down = flag;
	if (key == SDLK_LEFT)
		FLAGS.keydown_left = flag;
	if (key == SDLK_RIGHT)
		FLAGS.keydown_right = flag;
	if (key == SDLK_LSHIFT)
		FLAGS.speed = flag + 1;
	if (key == SDLK_KP_PLUS && flag && FLAGS.zoom < 5)
		FLAGS.zoom += 0.1;
	if (key == SDLK_KP_MINUS && flag && FLAGS.zoom > 1)
		FLAGS.zoom -= 0.1;
	if (EVENT.type == SDL_KEYDOWN && key == SDLK_t)
		FLAGS.textur = (FLAGS.textur == 0) ? 4 : 0;
}

static void	frame_count(t_wolf *wolf)
{
	FRAME.time_old = FRAME.time_new;
	FRAME.time_new = SDL_GetTicks();
	FRAME.frm_time = (FRAME.time_new - FRAME.time_old) / 1000.0;
	FRAME.spd_mv = FRAME.frm_time * 5.0;
	FRAME.spd_rotat = FRAME.frm_time * 3.0;
}

static void	finish(t_wolf *wolf)
{
	int i;

	i = -1;
	while (++i < 8)
		SDL_FreeSurface(BMP[i]);
	SDL_FreeSurface(SURF_WIN);
	SDL_DestroyWindow(WIN);
	SDL_Quit();
}

void		w_event(t_wolf *wolf)
{
	int game_on;
	int key;

	game_on = 1;
	while (game_on)
	{
		frame_count(wolf);
		while (SDL_PollEvent(&EVENT))
		{
			key = EVENT.key.keysym.sym;
			if (EVENT.type == SDL_QUIT
			|| (EVENT.type == SDL_KEYDOWN && key == SDLK_ESCAPE))
				game_on = 0;
			if (EVENT.type == SDL_KEYDOWN || EVENT.type == SDL_KEYUP)
				set_flags(wolf, key);
		}
		if (FLAGS.keydown_a || FLAGS.keydown_d
			|| FLAGS.keydown_up || FLAGS.keydown_down)
			w_moov_in_map(wolf);
		if (FLAGS.keydown_right || FLAGS.keydown_left)
			w_turn_left_right(wolf);
		w_raycasting(wolf);
	}
	finish(wolf);
}
