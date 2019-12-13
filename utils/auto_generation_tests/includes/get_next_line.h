/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 16:14:58 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/23 06:36:41 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

typedef struct		s_fd
{
	int				fd;
	char			*rest;
	int				len_rest;
	int				len_line;
	char			flags;
	struct s_fd		*next;
}					t_fd;

# define ADD 1
# define REMOVE 0
# define E_O_F (1 << 0)
# define B_ZERO (1 << 1)

# define END_LINE_CHAR '\n'

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

t_fd				*new_link(int fd);
t_fd				*manage_link(int fd, t_fd	**list, int add);
int					get_next_line(int fd, char **line);
int					to_read_or_not_to_read(t_fd *link, char **line);
int					enter_next_loop(char **line, t_fd *link);
int					update_line(char **line, t_fd *fd, const char *src,
		int len_src);
int					update_rest(const char *str, int start, int len_str, \
		t_fd *link);

#endif
