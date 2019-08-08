/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_key_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 17:41:42 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/12 17:41:45 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		w_turn_left_right(t_wolf *wolf)
{
	t_point	right;
	t_point	left;
	t_point	alpha;
	t_point	old_p;
	t_point	old_pl;

	if (FLAGS.keydown_left || FLAGS.keydown_right)
	{
		left = (t_point)
				{.y = cos(FRAME.spd_rotat), .x = sin(FRAME.spd_rotat)};
		right = (t_point)
				{.y = cos(-FRAME.spd_rotat), .x = sin(-FRAME.spd_rotat)};
		if (FLAGS.keydown_right == 1)
			alpha = left;
		if (FLAGS.keydown_left == 1)
			alpha = right;
		old_p = (t_point) {.x = LBRNT.ply_drct_x, .y = LBRNT.ply_drct_y};
		old_pl = (t_point) {.x = LBRNT.prjct_x, .y = LBRNT.prjct_y};
		LBRNT.ply_drct_x = old_p.x * alpha.y - old_p.y * alpha.x;
		LBRNT.ply_drct_y = (old_p.x * alpha.x) + (old_p.y * alpha.y);
		LBRNT.prjct_x = old_pl.x * alpha.y - old_pl.y * alpha.x;
		LBRNT.prjct_y = old_pl.x * alpha.x + old_pl.y * alpha.y;
	}
}

static void	step_right_left(t_wolf *wolf, double mv_x, double mv_y, double a)
{
	if (FLAGS.keydown_d == 1)
	{
		if (LBRNT.map[(int)LBRNT.ply_pstn_y]
			[(int)(LBRNT.ply_pstn_x - (mv_y * a))] != S_WALL)
			LBRNT.ply_pstn_x -= mv_y;
		if (LBRNT.map[(int)(LBRNT.ply_pstn_y + (mv_x * a))]
			[(int)LBRNT.ply_pstn_x] != S_WALL)
			LBRNT.ply_pstn_y += mv_x;
	}
	if (FLAGS.keydown_a == 1)
	{
		if (LBRNT.map[(int)LBRNT.ply_pstn_y]
			[(int)(LBRNT.ply_pstn_x + (mv_y * a))] != S_WALL)
			LBRNT.ply_pstn_x += mv_y;
		if (LBRNT.map[(int)(LBRNT.ply_pstn_y - (mv_x * a))]
			[(int)LBRNT.ply_pstn_x] != S_WALL)
			LBRNT.ply_pstn_y -= mv_x;
	}
}

static void	step_up_down(t_wolf *wolf, double mv_x, double mv_y, double a)
{
	if (FLAGS.keydown_down == 1)
	{
		if (LBRNT.map[(int)LBRNT.ply_pstn_y]
			[(int)(LBRNT.ply_pstn_x - (mv_x * a))] != S_WALL)
			LBRNT.ply_pstn_x -= mv_x;
		if (LBRNT.map[(int)(LBRNT.ply_pstn_y - (mv_y * a))]
			[(int)LBRNT.ply_pstn_x] != S_WALL)
			LBRNT.ply_pstn_y -= mv_y;
	}
	if (FLAGS.keydown_up == 1)
	{
		if (LBRNT.map[(int)LBRNT.ply_pstn_y]
			[(int)(LBRNT.ply_pstn_x + (mv_x * a))] != S_WALL)
			LBRNT.ply_pstn_x += mv_x;
		if (LBRNT.map[(int)(LBRNT.ply_pstn_y + (mv_y * a))]
			[(int)LBRNT.ply_pstn_x] != S_WALL)
			LBRNT.ply_pstn_y += mv_y;
	}
}

void		w_moov_in_map(t_wolf *wolf)
{
	double mv_x;
	double mv_y;
	double a;

	a = 3;
	mv_y = 0.03 * LBRNT.ply_drct_y * FLAGS.speed;
	mv_x = 0.03 * LBRNT.ply_drct_x * FLAGS.speed;
	if (FLAGS.keydown_down == 1 || FLAGS.keydown_up == 1)
		step_up_down(wolf, mv_x, mv_y, a);
	if (FLAGS.keydown_a == 1 || FLAGS.keydown_d == 1)
		step_right_left(wolf, mv_x, mv_y, a);
}
