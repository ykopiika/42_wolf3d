/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_print_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 21:44:13 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/21 21:44:15 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	print_textured_line(t_text t, int ray, t_raycast *v)
{
	int y;

	y = -1;
	while (++y < v->y_strt)
		t.data[(y * WDTH) + ray] = SKY_COLOR;
	y = v->y_strt;
	while (y < v->y_fnsh)
	{
		t.c = y * 256 - HGHT * 128 + v->hght_wall * 128;
		t.y_text = ((t.c * t.text_hght) / v->hght_wall) / 256;
		t.color_text = t.dat_bmp[t.text_hght * t.y_text + t.x_text];
		t.data[y * WDTH + ray] = t.color_text;
		y++;
	}
	y--;
	while (++y < HGHT)
		t.data[(y * WDTH) + ray] = FLOOR_COLOR;
}

static void	choose_right_texture(t_text *t, t_wolf *wolf, t_raycast *v)
{
	t->dat_bmp = BMP[0 + FLAGS.textur]->pixels;
	if ((v->ray_x_drct < 0 && v->ray_y_drct < 0)
		|| (v->ray_x_drct >= 0 && v->ray_y_drct < 0))
	{
		if (v->wall_side == 1)
			t->dat_bmp = BMP[1 + FLAGS.textur]->pixels;
	}
	if ((v->ray_x_drct < 0 && v->ray_y_drct >= 0)
		|| (v->ray_x_drct >= 0 && v->ray_y_drct >= 0))
	{
		if (v->wall_side == 1)
			t->dat_bmp = BMP[2 + FLAGS.textur]->pixels;
	}
	if ((v->ray_x_drct >= 0 && v->ray_y_drct < 0)
		|| (v->ray_x_drct >= 0 && v->ray_y_drct >= 0))
	{
		if (v->wall_side == 0)
			t->dat_bmp = BMP[3 + FLAGS.textur]->pixels;
	}
}

void		w_print_wall(t_wolf *wolf, t_raycast *v, int ray)
{
	t_text	t;

	t.text_wdth = 64;
	t.text_hght = 64;
	if (!v->wall_side)
		t.x_on_block = LBRNT.ply_pstn_y + v->distnc_wall * v->ray_y_drct;
	else
		t.x_on_block = LBRNT.ply_pstn_x + v->distnc_wall * v->ray_x_drct;
	t.x_on_block -= (int)(t.x_on_block);
	t.data = SURF_WIN->pixels;
	t.x_text = (int)(t.x_on_block * (double)t.text_wdth);
	if (v->wall_side == 0 && v->ray_x_drct > 0)
		t.x_text = t.text_wdth - t.x_text - 1;
	if (v->wall_side == 1 && v->ray_y_drct < 0)
		t.x_text = t.text_wdth - t.x_text - 1;
	choose_right_texture(&t, wolf, v);
	print_textured_line(t, ray, v);
}
