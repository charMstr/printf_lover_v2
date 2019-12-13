/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 22:29:55 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/26 04:59:23 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

/*
** note0: 	see #define in header if you want to change the END_LINE_CHAR
**
** note1: 	2nd set of conditions -> added feature:
**			if get_next_line() is called with NULL pointer it will remove/free
**			the potentially existing link matching the given filedescriptor.
**			therefore you can only read the first few lines and free the memory
**			then close the fd.
**
** note2:	this GNL is able to read binary files as it will return 2 if we
**			encouter a '\0' that is before the very end of the file.
**			we can either decide to add a '\n', or just print the empty string
**			alone, or even stop reding. if you want to print the line including
**			the backslash zero in case gnl returns 2: you will have to call
**			a ft_putstr_fd  modified, that will write len+1 characters.
**
**
** note3:	3rd set of conditions -> called only on the very frist time (static
**			pointer initialized to NULL). Head of a linked list, this allows
**			to read read on different file descriptors at the same time.
**
** RETURN: -1 error occured
**			0 EOF is reached, and there is nothing left in "fd->rest" string
**			1 the END_LINE_CHAR was met and there is still things to process.
**			2 an '\0' was met in a binary file, and EOF was not reached yet.
*/

int	get_next_line(int fd, char **line)
{
	static t_fd		*head;
	t_fd			*fd_link;
	int				result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!line)
		if (!manage_link(fd, &head, REMOVE))
			return (-1);
	*line = NULL;
	if (!head)
		if (!(head = new_link(fd)))
			return (-1);
	if (!(fd_link = manage_link(fd, &head, ADD)))
		return (-1);
	fd_link->len_line = 0;
	fd_link->flags &= ~B_ZERO;
	*line = 0;
	result = to_read_or_not_to_read(fd_link, line);
	if (result <= 0)
		manage_link(fd, &head, REMOVE);
	return (result);
}

/*
** note:	in this function we put whats read in line, and if a END_CHAR_LINE
**			is met we then place the rest in the string "rest", matching the
**			given filedescriptor (link->rest).
**
** RETURN:	as above.
*/

int	to_read_or_not_to_read(t_fd *link, char **line)
{
	int		bytes_read;
	char	buf[BUFFER_SIZE + 1];
	int		position;

	position = BUFFER_SIZE;
	if (link->len_rest)
		if ((position = enter_next_loop(line, link)) == -1)
			return (-1);
	while ((position == BUFFER_SIZE) && !(link->flags & (B_ZERO | E_O_F)))
	{
		if ((bytes_read = read(link->fd, buf, BUFFER_SIZE)) == -1)
			return (-1);
		if (bytes_read < BUFFER_SIZE)
			link->flags |= E_O_F;
		if ((position = update_line(line, link, buf, bytes_read)) == -1)
			return (-1);
		if (!update_rest(buf, position, bytes_read, link))
			return (-1);
	}
	if (((link->flags & E_O_F) == E_O_F) && !link->len_rest)
		return (0);
	return ((link->flags & B_ZERO) == B_ZERO) ? 2 : 1;
}

/*
** note:	this function will be called if there was some left-overs in
**			fd->rest, from the previous call to get_next_line on that fd.
**
**			if yes it will update both line and rest starting at + 1 index,
**			assuming that if there is a rest its because we met a character we
**			want to now skip.
**
** RETURN:	BUFFER_SIZE to validate the next loop condition if length of rest
**				is now 0.
**			0 if there is still characters in rest string.
**			-1 if a problem occured.
*/

int	enter_next_loop(char **line, t_fd *link)
{
	int	position;

	if ((position = update_line(line, link, link->rest + 1, \
					link->len_rest - 1)) == -1)
		return (-1);
	if (!update_rest(link->rest + 1, position, link->len_rest - 1, link))
		return (-1);
	if (link->len_rest == 0)
		return (BUFFER_SIZE);
	return (0);
}

/*
** note:	this function will update line, and if a binary_zero value is found
**			before the lenght of bytes to be read, then the fd->b_zero flag is
**			activated.
**
** RETURN:	the position where the END_LINE_CHAR or '\0' was found.
*/

int	update_line(char **line, t_fd *link, const char *src, int len_src)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = *line;
	i = -1;
	j = -1;
	while (++i < len_src)
		if (!src[i] || src[i] == END_LINE_CHAR)
			break ;
	link->flags |= (src[i] == '\0' && i < len_src) ? B_ZERO : 0x0;
	if (!(*line = (char*)malloc(sizeof(char) * (link->len_line + i + 1))))
		return (-1);
	(*line)[link->len_line + i] = '\0';
	while (++j < link->len_line + i)
	{
		if (j < link->len_line)
			(*line)[j] = tmp[j];
		else
			(*line)[j] = src[j - link->len_line];
	}
	link->len_line = link->len_line + i;
	free(tmp);
	return (i);
}

/*
** note:	this function will update the string fd->rest. and te rest_len,
**			reading in the char *str, starting at start position, until len_str
**			char are read.
**
** RETURN:	1 if ok
**			0 if malloc failed
*/

int	update_rest(const char *str, int start, int len_str, t_fd *link)
{
	int		i;
	char	*tmp;
	int		len;

	len = (len_str - start < 0) ? 0 : len_str - start;
	tmp = link->rest;
	i = -1;
	if (!(link->rest = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	link->rest[len] = '\0';
	while (++i < len)
		link->rest[i] = str[start + i];
	link->len_rest = len;
	free(tmp);
	return (1);
}
