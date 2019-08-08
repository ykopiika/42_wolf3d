/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:19:41 by ykopiika          #+#    #+#             */
/*   Updated: 2018/11/09 14:19:53 by ykopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;
	char	*s1;

	s1 = (char*)s;
	len = 0;
	while (s1 && *s1)
	{
		len++;
		s1++;
	}
	return (len);
}
