/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 14:24:10 by hlatt             #+#    #+#             */
/*   Updated: 2026/11/12 22:55:31 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	init_stash(t_stash *stash)
{
	if (!stash || BUFFER_SIZE <= 0)
		return (-1);
	stash->len = 0;
	stash->capacity = BUFFER_SIZE;
	stash->content = malloc((size_t)stash->capacity + 1);
	if (!stash->content)
		return (-1);
	stash->content[0] = '\0';
	return (0);
}

int	str_len(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*resize_stash(t_stash *stash, char *buf, int bytes_read,
		int new_capacity)
{
	char	*block;

	if (!stash || !stash->content || !buf || bytes_read < 0
		|| new_capacity < stash->len
		|| bytes_read > new_capacity - stash->len)
		return (NULL);
	block = malloc((size_t)new_capacity + 1);
	if (!block)
		return (NULL);
	copy_data(block, stash->content, stash->len);
	copy_data(block + stash->len, buf, bytes_read);
	block[new_capacity] = '\0';
	return (block);
}

int	str_index(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	copy_data(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}
