/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlatt <hlatt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 14:24:10 by hlatt             #+#    #+#             */
/*   Updated: 2026/11/12 15:53:37 by hlatt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	str_len(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	str_index(const char *s, int c)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

int	init_stash(t_stash *stash)
{
	if (!stash)
		return (-1);
	stash->len = 0;
	stash->capacity = BUFFER_SIZE;
	stash->content = malloc(stash->capacity + 1);
	if (!stash->content)
		return (-1);
	stash->content[0] = '\0';
	return (0);
}

void	copy_data(char *dst, const char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

char	*resize_stash(t_stash *stash, char *buf, int bytes_read,
		int new_capacity)
{
	int		required_len;
	char	*block;

	required_len = stash->capacity;
	while (required_len < new_capacity)
		required_len = required_len * 2;
	block = malloc(required_len + 1);
	if (!block)
		return (NULL);
	copy_data(block, stash->content, stash->len);
	copy_data(block + stash->len, buf, bytes_read);
	block[new_capacity] = '\0';
	return (block);
}
