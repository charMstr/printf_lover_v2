/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRF_build_function_files_assist.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 23:24:12 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/13 20:27:34 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PRF.h"
#include "../includes/get_next_line.h"

/*
** this file will assist in creating the .c files, it will contain the
** functions that do anything afer writing the definition of the function and
** the opened "{". and before the closing of the file with return (0);...
*/

/*
** note:	this function will build a line that is fit for the debbug once we
**			sed the .c file into a copy replacing printf() calls by ft_printf()
**			then showing the diff
**
** note:	for a future sed command, the debug line starts by a captalilzed
**			'P'
**
** note:	since "n" specifier is storing data we will add an extra
**			printf("%d\n", n); call
**
** RETURN:	1 if ok
**			0 if (failure)
*/

int writing_test_call(int fd_w, char *line, char *specifier, int *count)
{
	char	*debug;

	ft_putstr_fd("\tmy_ft_putstr_fd(\"", fd_w);
	if (!(debug = ft_stringify(line)))
		return (0);
	debug[0] = 'P';
	ft_putstr_fd(debug, fd_w);
	ft_putstr_fd("\t==>\t", fd_w);
	ft_putendl_fd("\", 1);", fd_w);
	ft_putstr_fd("\t", fd_w);
	ft_putendl_fd(line, fd_w);
	if (!ft_strncmp(specifier, "n", 1))
	{
		(*count)++;
		ft_putstr_fd("\tmy_ft_putnbr_fd(n, 1);\n", fd_w);
		ft_putstr_fd("my_ft_putstr_fd(\"\\n\", 1);\n", fd_w);
	}
	free(debug);
	return (1);
}

/*
** note:	this function will build a line that will assert the result from
**			the original printf and the ft_printf;
**
** note2:	we remove the ";" at the end of line so that it can be added into
**			the assert() parenthesis.
**
** RETURN:	1 if (ok)
**			0 if (failed)
*/

int writing_assert_call(int fd_w, char *line, int *count)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] == ';')
			line[i] = '\0';
	ft_putstr_fd("assert(", fd_w);
	ft_putstr_fd(line, fd_w);
	ft_putstr_fd(" == ", fd_w);
	ft_putstr_fd("ft_", fd_w);
	ft_putstr_fd(line, fd_w);
	ft_putendl_fd(");", fd_w);
	(*count)++;
	return (1);
}

/*
** note:	this function will name the new file.c either in the
**			../generated_tests directory, or in the ../generated_tests/asserts
**			subdirectory, it takes as input the name of the last tmp_file build
**			in the temporay processes.
**
** RETURN:	char *name of the new .c file
**			NULL if failure
*/

char *creat_name_for_c_file(char *tmp_name, int option)
{

	char *new_name;
	char *tmp;

	if (!(new_name = ft_substr(tmp_name, 13, ft_strlen(tmp_name))))
		return (NULL);
	tmp = new_name;
	if (!(new_name = ft_strjoin(new_name, ".c")))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	tmp = new_name;
	if (option == ASSERT_TEST)
		if (!(new_name = ft_strjoin("../generated_tests/assert_tests/sources/", new_name)))
		{
			free(tmp);
			return (NULL);
		}
	if (option == NORMAL_TEST)
		if (!(new_name = ft_strjoin("../generated_tests/sources/", new_name)))
		{
			free(tmp);
			return (NULL);
		}
	free(tmp);
	return (new_name);
}
