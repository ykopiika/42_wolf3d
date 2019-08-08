/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_valid_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:15:43 by ykopiika          #+#    #+#             */
/*   Updated: 2019/07/05 18:15:46 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_read	*malloc_lst(t_read *read, char *str, int fd)
{
	if (!read)
	{
		if (!(read = (t_read *)malloc(sizeof(t_read))))
			w_error(ERR_MALLOC, fd);
		read->line = ft_strdup(str);
		read->row = 0;
		read->len = ft_strlen(str);
		read->next = NULL;
		read->prev = NULL;
		return (read);
	}
	else
	{
		read->next = (t_read *)malloc(sizeof(t_read));
		if (!read->next)
			w_error(ERR_MALLOC, fd);
		read->next->line = ft_strdup(str);
		read->next->row = read->row + 1;
		read->next->len = ft_strlen(str);
		read->next->next = NULL;
		read->next->prev = read;
		return (read->next);
	}
}

static void		cheack_line(t_wolf *wolf, int i, int j, t_read *lst)
{
	if (i == 0 || i == (LBRNT.size - 1))
	{
		j = -1;
		while (++j < lst->len)
			if (lst->line[j] != S_WALL)
				w_error(ERR_WALL, wolf->fd);
	}
	j = -1;
	while (++j < lst->len)
	{
		if (!FLAGS.free_sp && lst->line[j] == S_FREE && (FLAGS.free_sp = 1))
		{
			LBRNT.ply_pstn_x = j + 0.5;
			LBRNT.ply_pstn_y = lst->row + 0.5;
		}
		if (!FLAGS.player && lst->line[j] == S_PLYR && (FLAGS.player = 1))
		{
			LBRNT.ply_pstn_x = j + 0.5;
			LBRNT.ply_pstn_y = lst->row + 0.5;
		}
		if (lst->line[j] != S_FREE && lst->line[j] != S_PLYR
			&& lst->line[j] != S_WALL)
			w_error(ERR_WRONG_SYMBOL, wolf->fd);
	}
}

static void		w_valid_read(t_wolf *wolf)
{
	int		i;
	int		j;
	t_read	*lst;

	i = 0;
	j = -1;
	lst = READ;
	LBRNT.map = (char**)malloc(sizeof(char*) * LBRNT.size);
	if (!LBRNT.map)
		w_error(ERR_MALLOC, wolf->fd);
	while (lst)
	{
		cheack_line(wolf, i, j, lst);
		LBRNT.map[i] = lst->line;
		lst = lst->next;
		i++;
	}
	if (i != LBRNT.size)
		w_error(ERR_HEIGHT, wolf->fd);
	if (FLAGS.free_sp == 0 && FLAGS.player == 0)
		w_error(ERR_FREE, wolf->fd);
}

void			w_valid_map(t_wolf *wolf, int fd)
{
	int		gnl;
	char	*string;

	gnl = 0;
	string = NULL;
	READ = NULL;
	while ((gnl = get_next_line(fd, &string)) == 1)
	{
		READ = malloc_lst(READ, string, wolf->fd);
		if (READ->row == 0)
			LBRNT.size = READ->len;
		if (READ->len != LBRNT.size || LBRNT.size <= 3 || LBRNT.size > 100)
			w_error(ERR_LENGTH, wolf->fd);
		if ((READ->line[0] != S_WALL) || (READ->line[READ->len - 1] != S_WALL))
			w_error(ERR_WALL, wolf->fd);
		if (READ->row >= LBRNT.size)
			w_error(ERR_HEIGHT, wolf->fd);
		ft_strdel(&string);
	}
	if ((READ == NULL) || gnl == -1)
		w_error(ERR_ARGV, wolf->fd);
	while (READ->prev != NULL)
		READ = READ->prev;
	w_valid_read(wolf);
}
