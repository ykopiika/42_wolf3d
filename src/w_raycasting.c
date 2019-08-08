/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_raycasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:20:38 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/17 18:20:41 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	count_side_dist(t_raycast *v)
{
	v->x_mp = (int)v->ply_pstn_x;
	v->y_mp = (int)v->ply_pstn_y;
	if (v->ray_x_drct < 0)
	{
		v->x_stage = -1;
		v->strt_dlt_x = (v->ply_pstn_x - v->x_mp) * v->dlt_x;
	}
	else
	{
		v->x_stage = 1;
		v->strt_dlt_x = (v->x_mp + 1.0 - v->ply_pstn_x) * v->dlt_x;
	}
	if (v->ray_y_drct < 0)
	{
		v->y_stage = -1;
		v->strt_dlt_y = (v->ply_pstn_y - v->y_mp) * v->dlt_y;
	}
	else
	{
		v->y_stage = 1;
		v->strt_dlt_y = (v->y_mp + 1.0 - v->ply_pstn_y) * v->dlt_y;
	}
}

static void	count_len_ray(t_wolf *wolf, t_raycast *v)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (v->strt_dlt_x < v->strt_dlt_y)
		{
			v->strt_dlt_x += v->dlt_x;
			v->x_mp += v->x_stage;
			v->wall_side = 0;
		}
		else
		{
			v->strt_dlt_y += v->dlt_y;
			v->y_mp += v->y_stage;
			v->wall_side = 1;
		}
		if (LBRNT.map[v->y_mp][v->x_mp] == S_WALL)
			hit = 1;
	}
}

static void	count_hight_wall(t_raycast *v)
{
	if (!v->wall_side)
		v->distnc_wall =
			(v->x_mp - v->ply_pstn_x + (1.0f - v->x_stage) / 2) / v->ray_x_drct;
	else
		v->distnc_wall =
			(v->y_mp - v->ply_pstn_y + (1.0f - v->y_stage) / 2) / v->ray_y_drct;
	v->hght_wall = (int)(HGHT / v->distnc_wall);
	v->y_strt = (-v->hght_wall >> 1u) + (HALF_HGHT);
	if (v->y_strt < 0)
		v->y_strt = 0;
	v->y_fnsh = (v->hght_wall >> 1u) + (HALF_HGHT);
	if (v->y_fnsh >= HGHT)
		v->y_fnsh = HGHT - 1;
}

void		w_raycasting(t_wolf *wolf)
{
	t_raycast v;

	v.ray = 0;
	v.ply_pstn_x = LBRNT.ply_pstn_x;
	v.ply_pstn_y = LBRNT.ply_pstn_y;
	v.ply_drct_x = LBRNT.ply_drct_x;
	v.ply_drct_y = LBRNT.ply_drct_y;
	v.prjct_x = LBRNT.prjct_x;
	v.prjct_y = LBRNT.prjct_y;
	while (v.ray < LBRNT.rays)
	{
		v.scrn_x = 1 - (2.0 * (double)v.ray / LBRNT.rays);
		v.ray_x_drct = v.ply_drct_x * FLAGS.zoom + v.prjct_x * v.scrn_x;
		v.ray_y_drct = v.ply_drct_y * FLAGS.zoom + v.prjct_y * v.scrn_x;
		v.dlt_x = fabs(1 / v.ray_x_drct);
		v.dlt_y = fabs(1 / v.ray_y_drct);
		count_side_dist(&v);
		count_len_ray(wolf, &v);
		count_hight_wall(&v);
		w_print_wall(wolf, &v, v.ray);
		v.ray++;
	}
	if (SDL_UpdateWindowSurface(WIN) != 0)
		w_error(ERR_SDL, -42);
}
