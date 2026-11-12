/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 14:46:15 by hlatt             #+#    #+#             */
/*   Updated: 2026/11/12 22:54:46 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef OPEN_MAX
# define OPEN_MAX 1024
#endif

char	*get_next_line(int fd)
{
	static t_stash	stashes[OPEN_MAX];
	t_stash			*stash;
	char			*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	stash = &stashes[fd];
	if (!stash->content && init_stash(stash) < 0)
		return (NULL);
	if (fill_stash(fd, stash) < 0)
	{
		free(stash->content);
		*stash = (t_stash){0};
		return (NULL);
	}
	line = extract_line(stash);
	if (!line)
	{
		free(stash->content);
		*stash = (t_stash){0};
		return (NULL);
	}
	update_stash(stash);
	return (line);
}

int	fill_stash(int fd, t_stash *stash)
{
	char	buf[BUFFER_SIZE];
	int		bytes_read;

	while (str_index(stash->content, '\n') == -1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (-1);
		if (bytes_read == 0)
			return (0);
		if (append(stash, buf, bytes_read) < 0)
			return (-1);
	}
	return (1);
}

int	append(t_stash *stash, char *buf, int bytes_read)
{
	int		new_capacity;
	char	*new_content;

	if (!stash || !buf || bytes_read < 0
		|| bytes_read > INT_MAX - stash->len)
		return (-1);
	new_capacity = stash->len + bytes_read;
	if (new_capacity > stash->capacity)
	{
		new_content = resize_stash(stash, buf, bytes_read, new_capacity);
		if (!new_content)
			return (-1);
		free(stash->content);
		stash->content = new_content;
		stash->capacity = new_capacity;
	}
	else
		copy_data(stash->content + stash->len, buf, bytes_read);
	stash->len = new_capacity;
	stash->content[stash->len] = '\0';
	return (0);
}

char	*extract_line(t_stash *stash)
{
	int		newline;
	int		line_len;
	char	*line;

	if (!stash || !stash->content || stash->len == 0)
		return (NULL);
	newline = str_index(stash->content, '\n');
	line_len = stash->len;
	if (newline >= 0)
		line_len = newline + 1;
	line = malloc((size_t)line_len + 1);
	if (!line)
		return (NULL);
	copy_data(line, stash->content, line_len);
	line[line_len] = '\0';
	return (line);
}

void	update_stash(t_stash *stash)
{
	int	newline;
	int	remaining;

	newline = str_index(stash->content, '\n');
	if (newline < 0)
		stash->len = 0;
	else
	{
		remaining = stash->len - newline - 1;
		copy_data(stash->content, stash->content + newline + 1, remaining);
		stash->len = remaining;
	}
	stash->content[stash->len] = '\0';
}
