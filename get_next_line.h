/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 15:32:05 by hlatt             #+#    #+#             */
/*   Updated: 2026/11/12 22:54:33 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_stash
{
	char	*content;
	int		len;
	int		capacity;
}			t_stash;

char		*get_next_line(int fd);
int			init_stash(t_stash *stash);
int			fill_stash(int fd, t_stash *stash);
int			append(t_stash *stash, char *buf, int bytes_read);
char		*extract_line(t_stash *stash);
void		update_stash(t_stash *stash);

int			str_len(char *str);
char		*resize_stash(t_stash *stash, char *buf, int bytes_read,
				int new_capacity);
int			str_index(char *str, char c);
void		copy_data(char *dst, char *src, int len);

#endif