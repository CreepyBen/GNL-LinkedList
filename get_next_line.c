/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlatt <hlatt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 14:46:15 by hlatt             #+#    #+#             */
/*   Updated: 2026/11/12 15:52:54 by hlatt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	append(t_stash *stash, char *buf, int bytes_read)
{
	int		new_capacity;
	char	*block;

	new_capacity = stash->len + bytes_read;
	if (new_capacity <= stash->capacity)
	{
		copy_data(stash->content + stash->len, buf, bytes_read);
		stash->len = new_capacity;
		stash->content[stash->len] = '\0';
		return (0);
	}
	block = resize_stash(stash, buf, bytes_read, new_capacity);
	free(stash->content);
	stash->len = new_capacity;
	stash->capacity = required_len;
	stash->content = block;
	return (0);
}
