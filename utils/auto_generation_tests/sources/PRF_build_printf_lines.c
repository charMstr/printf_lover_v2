/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRF_start_build_printf_lines.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:09:06 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/04 04:57:57 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PRF.h"
#include "../includes/get_next_line.h"

/*
** note:	this function is the root of the logic branch building a file
**			containing on each lines a printf valid call. it uses the
**			previsously made temporary file containing the combo_<specifier>
**			(flags+conversions_specifications)
**
** RETURN:	char * name of the file created.
**			NULL if failure
*/

char *build_printf_file(char* file_read, char *specifier, int range)
{
	int fd_r;
	int fd_w;
	char *file_name;

	if (!(file_name = create_name("../tmp_files/test_func_", specifier)))
	{
		failure("failed to name file in build_printf_file()");
		return (NULL);
	}
	if((fd_r = open(file_read, O_RDONLY)) == -1)
	{
		failure("failed to open/read in build_printf_file()");
		free(file_name);
		return (NULL);
	}
	if((fd_w = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644)) == -1)
	{
		failure("failed to open/read in build_printf_file()");
		close(fd_r);
		free(file_name);
		return (NULL);
	}
	if (!build_printf_line(fd_r, fd_w, specifier, range))
	{
		failure("build_printf_line() failed in build_printf_file()");
		close(fd_r);
		close(fd_w);
		free(file_name);
		return (NULL);
	}
	close(fd_r);
	close(fd_w);
	return (file_name);
}

/*
** note:	this function is called by the root function at the top which did
**			open the file descriptors for us, and created the new_file name.
**
** note:	it will get a line after another from the fd_r and it will process
**			each line in a subfunction (passing forward fd_w ...).
**			the sub function will print on each line a proper printf call.
**
** RETURN:	1 for success
**			0 for failure
*/

int build_printf_line(int fd_r, int fd_w, char *specifier, int range)
{
	char *line;
	char *new;

	while (get_next_line(fd_r, &line))
	{
		if (!(new = start_build_printf_line(line, specifier)))
		{
			free(line);
			return (failure("start_build_printf_line() failed in build_printf_line()"));
		}
		if (!(ft_strncmp(specifier, "p", 4)) \
			|| !(ft_strncmp(specifier, "f", 4)) \
			|| !(ft_strncmp(specifier, "g", 4)) \
			|| !(ft_strncmp(specifier, "e", 4)))
			range = 16;
		if (!(finish_build_printf_line(new, specifier, fd_w, range, 0)))
		{
			free(line);
			free(new);
			return (failure("start_build_printf_line() failed in build_printf_line()"));
		}
		free(new);
		free(line);
	}
	free(line);
	return (1);
}

/*
** note:	this function will do all the hard work, it will take a line,
**			and creat all the possible end of printf calls, according to the
**			specifier and the eventual presence of "*" or not.
**
**			if a star is found (starting the search at line + start) then we
**			call a function that will recurce if needed.
**			if the star is not found, we terminate adding "<specifier> and ");"
**			and print it to the given filedescriptor.
**
** note2:	we choose not to replace the stars when the specifier is "n" since
**			this case is special. "%" was replaced with "%%" in front of the
**			the flags so that they became just litteral characters, not format
**			string.
**
** RETURN:	1 if success
**			0 if failed
*/

int	finish_build_printf_line(char *line, char *specifier, int fd_w, int range, int start)
{
	char	*location;
	int		i;
	char	*new;

	i = - range - 1;
	if (!(ft_strncmp(specifier , "n", 1)) || !(location = ft_strchr(line + start, '*')))
	 	append_end_to_call(line, specifier, fd_w);
	else
	{
		while (++i <= range)
		{
			if (!(new = substitute_star(line, i)))
				return (failure("substitute_star() failed in \
							finish_build_printf_line()"));
			if (!(location = ft_strchr(line + (location - line), '*')))
				append_end_to_call(new, specifier, fd_w);
			else
			{
				if (!(finish_build_printf_line(new, specifier, fd_w, range, \
								location - line + 1)))
				{
					free(new);
					return (failure("finish_build_printf_line() failed in a \
								recursion call"));
				}
			}
			free(new);
		}
	}
	return (1);
}

/*
** note:	this function will simply append the number given as argument to
**			the line given as argument. it will also append the ", "
**
** RETURN:	char *, new line appended
**			NULL if failure
*/

char *substitute_star(char *line, int num)
{
	char *new;
	char *tmp;
	char *number_str;

	if (!(new = ft_strjoin(line, ", ")))
		return (NULL);
	if (!(number_str = ft_itoa(num)))
	{
		free(new);
		return (NULL);
	}
	tmp = new;
	if (!(new = ft_strjoin(new, number_str)))
	{
		free(tmp);
		free(number_str);
		return (NULL);
	}
	free(tmp);
	free(number_str);
	return (new);
}

/*
** note:	this function will terminate the call to prIntf() line. it will
**			jsut write to the given fildescriptor, in he case there is a n, we
**			write &n.
**			Else in any oher case than "%" we write the specifer, then we close
**			the call.
*/

void	append_end_to_call(char *line, char *specifier, int fd_w)
{
	ft_putstr_fd(line, fd_w);
	if (!(ft_strncmp(specifier, "n", 2)))
		ft_putstr_fd(", &n", fd_w);
	else if (ft_strncmp(specifier, "%", 2))
	{
		ft_putstr_fd(", ", fd_w);
		ft_putstr_fd(specifier, fd_w);
	}
	ft_putendl_fd(");", fd_w);
}

/*
** note:	this function will take as input a line from the previously made
**			file containing flags+conversion_specifiers ex: "combo_d"
**			It does 3 joins, and build the start of a printf call line.
**
** note:	in the case of specifier = "n" we manage the special case in a
**			subfunction;
**
** RETURN:	char * if ok
**			NULL if failure
*/

char *start_build_printf_line(char *line, char *specifier)
{
	char *new;
	char *tmp;

	if (!(ft_strncmp(specifier, "n", 4)))
	{
		if (!(new = manage_the_n_case(line, specifier)))
			return (NULL);
	}
	else
	{
		if (!(new = ft_strjoin("printf(\"-->|%", line)))
			return (NULL);
		tmp = new;
		if (!(new = ft_strjoin(new, specifier)))
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
		tmp = new;
		if (!(new = ft_strjoin(new, "|<--\\n\"")))
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
	}
	return (new);
}

/*
** note:	this function has been added to differenciate any case from the
**			the special case when the specifier is "n".
**			if its not "n" we just added the specifier, then join the rest of
**			the printf call with something that finishes with a '\n'.
**
**			if the specifier is "n" then we add "%n" in place of the specifier
**			within the string format, then we do not add a '\n' in the line to
**			be printed, this is for debbug purpose. so that we can
**			follow the call with a printf("%d\n", n);
**
** RETURN:	char * line
**			NULL if (failure)
*/

char *manage_the_n_case(char *line, char *specifier)
{
	char *new;
	char *tmp;

	if (!(new = ft_strjoin("printf(\"-->|%%", line)))
		return (NULL);
	tmp = new;
	if (!(new = ft_strjoin(new, "%")))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	tmp = new;
	if (!(new = ft_strjoin(new, specifier)))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	tmp = new;
	if (!(new = ft_strjoin(new, "|<--\"")))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (new);
}
