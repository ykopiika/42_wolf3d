/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 12:47:20 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/22 20:25:42 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "SDL2/SDL.h"
# include "SDL2_image/SDL_image.h"

# define WIN		wolf->sdl_data.win
# define EVENT		wolf->sdl_data.evnts
# define SURF_WIN	wolf->sdl_data.surf_win
# define BMP		wolf->sdl_data.bmp
# define READ		wolf->read
# define FLAGS		wolf->flags
# define LBRNT		wolf->lbrnt
# define FRAME		wolf->frame

# define S_PLYR		wolf->smbl.plyr
# define S_WALL		wolf->smbl.wall
# define S_FREE		wolf->smbl.free

# define SKY_COLOR		0x96efff
# define FLOOR_COLOR	0x252626

# define ERR_USAGE			0
# define ERR_MALLOC			1
# define ERR_SDL			2
# define ERR_ARGV			3
# define ERR_LENGTH			4
# define ERR_HEIGHT			5
# define ERR_WALL			7
# define ERR_FREE			8
# define ERR_WRONG_SYMBOL	9

# define WDTH			1200
# define HGHT			800
# define HALF_HGHT		400

typedef struct			s_labyrinth
{
	int					size;
	int					rays;
	char				**map;
	double				ply_pstn_x;
	double				ply_pstn_y;
	double				ply_drct_x;
	double				ply_drct_y;
	double				prjct_x;
	double				prjct_y;

}						t_labyrinth;

typedef struct			s_sdl_ptr
{
	SDL_Window			*win;
	SDL_Surface			*surf_win;
	SDL_Surface			**bmp;
	SDL_Event			evnts;
}						t_sdl_ptr;

typedef struct			s_read
{
	char				*line;
	int					row;
	int					len;

	struct s_read		*next;
	struct s_read		*prev;
}						t_read;

typedef struct			s_flags
{
	int					free_sp;
	int					player;
	double				zoom;

	int					keydown_a;
	int					keydown_d;
	int					keydown_up;
	int					keydown_down;
	int					keydown_right;
	int					keydown_left;
	int					textur;
	int					speed;
}						t_flags;

typedef struct			s_raycast
{
	int					x_stage;
	int					y_stage;
	int					wall_side;
	int					ray;
	int					x_mp;
	int					y_mp;
	int					hght_wall;
	int					y_strt;
	int					y_fnsh;
	double				ply_pstn_x;
	double				ply_pstn_y;
	double				ply_drct_x;
	double				ply_drct_y;
	double				prjct_x;
	double				prjct_y;
	double				scrn_x;
	double				ray_x_drct;
	double				ray_y_drct;
	double				strt_dlt_x;
	double				strt_dlt_y;
	double				dlt_x;
	double				dlt_y;
	double				distnc_wall;
}						t_raycast;

typedef struct			s_text
{
	int					*dat_bmp;
	int					text_wdth;
	int					text_hght;
	int					*data;
	int					c;
	int					x_text;
	int					y_text;
	int					color_text;
	double				x_on_block;
}						t_text;

typedef struct			s_point
{
	double				x;
	double				y;
}						t_point;

typedef struct			s_symb_lab
{
	char				plyr;
	char				free;
	char				wall;
}						t_symb_lab;

typedef struct			s_frame
{
	double				time_new;
	double				time_old;
	double				frm_time;
	double				spd_mv;
	double				spd_rotat;
}						t_frame;

typedef struct			s_wolf
{
	int					fd;
	t_labyrinth			lbrnt;
	t_symb_lab			smbl;
	t_sdl_ptr			sdl_data;
	t_read				*read;
	t_flags				flags;

	t_frame				frame;
}						t_wolf;

void					w_error(int err_nb, int fd);
void					w_valid_map(t_wolf *wolf, int fd);
void					w_raycasting(t_wolf *wolf);
void					w_moov_in_map(t_wolf *wolf);
void					w_turn_left_right(t_wolf *wolf);
void					w_event(t_wolf *wolf);
void					w_print_wall(t_wolf *wolf, t_raycast *v, int ray);

#endif
