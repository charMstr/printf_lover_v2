/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRF_build_function_files.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 21:25:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/13 14:53:15 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PRF.h"
#include "../includes/get_next_line.h"

/*
** This file will take care of producing for each specifier from tab[i], a
** fully compilable .c file that contains a function for a given specifier.
**
** the special case where "n" is the specifier leads to adding an extra line
** where we call printf("%d\n", n); to display what we stored in &n.
*/


/*
** note:	this function will be the root call for the branching taking care
**			of creating a .c file.
**
** note2:	it will Open the file to read ex: ../tmp_files/test_func_hx, and as
**			well open the file that will be created ready to receive the c
**			code.
**
** RETURN:	1 ok
**			0 failure
*/

int build_function_files(char *file_r, char *specifier, int option)
{
	char *new_name;
	int fd_r;
	int fd_w;

	if (!(new_name = creat_name_for_c_file(file_r, option)))
		return (0);
	if((fd_r = open(file_r, O_RDONLY)) == -1)
	{
		free(new_name);
		return (0);
	}
	if((fd_w = open(new_name, O_CREAT | O_RDWR | O_TRUNC, 0666)) == -1)
	{
		close(fd_r);
		free(new_name);
		return (0);
	}
	if (!(get_line_build_func_file(fd_r, fd_w, specifier, option)))
	{
		close(fd_r);
		close(fd_w);
		free(new_name);
		return (0);
	}
	close(fd_r);
	close(fd_w);
	success("created:\n\t");
	success_endl(new_name);
	free(new_name);
	return (1);
}

/*
** note:	this function will initiate the .c file, writting the prototype as
**			well (all this is done in a subfunction).
**
** note2:	Then it will get each line from the file to be read and manage it
**			in a subfunction which will print a stringified version of the call
**			for debug purpose on th esame line.(without '\n').
**			then if we are in the special case of the "n" specifier will add
**			an extra debug line.
**
** note3:	then it terminates the .c file.
**
** RETURN:	1 if ok
**			0 if failure
*/

int	get_line_build_func_file(int fd_r, int fd_w, char *specifier, int option)
{
	char	*line;
	int		result;
	int		count_lines;

	count_lines = 0;
	if (!(initiate_beggining_func_file(fd_w, specifier, option)))
		return (0);
	while ((result = get_next_line(fd_r, &line)) > 0)
	{
		if (option == NORMAL_TEST)
			if (!writing_test_call(fd_w, line, specifier, &count_lines))
				return (0);
		if (option == ASSERT_TEST)
			if (!writing_assert_call(fd_w, line, &count_lines))
				return (0);
		count_lines += 1;
		free(line);
	}
	if (result == -1)
		return (0);
	ft_putstr_fd("\treturn(0);\n}\n/*\n** charmstr@student.42.fr\n**\n** ", \
			fd_w);
	ft_putnbr_fd(count_lines, fd_w);
	ft_putendl_fd(" different calls generated automatically according to your \
options\n*/", fd_w);
	free(line);
	return (1);
}

/*
** note:	this function will initiate the .c file containing a
**			specifier-specific function. (prototype and name);
**
** note:	"%" is written in hard since the c standard does no tallow the
**			character in function name.
**
** RETURN:	1 if (ok)
**			0 if (failure)
*/

int	initiate_beggining_func_file(int fd_w, char *specifier, int option)
{
	char *proto_end;

	ft_putstr_fd("/*\n** charmstr@student.42.fr\n*/\n\n#include <stdio.h>\n", fd_w);
	if (option == ASSERT_TEST)
	{
		ft_putstr_fd("#include <assert.h>\n#include \
\"../includes/printf_lover_test_func.h\"\n\nint\t", fd_w);
	}
	else
		ft_putstr_fd("#include \
\"../includes/printf_lover_test_func.h\"\n\nint\t", fd_w);
	//if (option == ASSERT_TEST)
	//	ft_putstr_fd("assert_", fd_w);
	ft_putstr_fd("test_func_", fd_w);
	if (!(ft_strncmp(specifier, "%", 1)))
		ft_putstr_fd("percent", fd_w);
	else
		ft_putstr_fd(specifier, fd_w);
	ft_putstr_fd("(", fd_w);
	if (!(proto_end = get_prototype_end(specifier)))
		return (0);
	ft_putstr_fd(proto_end, fd_w);
	free(proto_end);
	ft_putendl_fd(")\n{\nsetbuf(stdout, NULL);", fd_w);
	return (1);
}

/*
** note:	this function should give the string that needs to be included in
**			the end of the function definition.
**
** note1:	special case: for "%" we do add void and nothing else
**
** RETURN:	char *
**			NULL if (failure)
*/

char *get_prototype_end(char *specifier)
{
	char *prototype_end;

	if (!ft_strncmp(specifier, "%", 1))
		return (get_type(specifier));
	if (!(prototype_end = ft_strjoin(get_type(specifier), specifier)))
		return (NULL);
	return (prototype_end);
}

/*
** note:	this function will get the type matching the specifier given as a
**			string in argument, and put the type litterally in a char *.
**
** RETURN:	char *containing a c code type: ex: "int"
**			NULL if failed
*/

char *get_type(char *specifier)
{
	if (!specifier)
		return (NULL);
	if (!(ft_strncmp(specifier, "hh", 2)))
		return (ft_strdup("signed char "));
	if (!(ft_strncmp(specifier, "h", 1)))
		return (ft_strdup("short int "));
	if (!(ft_strncmp(specifier, "ll", 2)))
		return (ft_strdup("long long int "));
	if (!(ft_strncmp(specifier, "l", 1)))
		return (ft_strdup("long int "));
	if (specifier[0] == 'd' || specifier[0] == 'i' || specifier[0] == 'c' \
		|| specifier[0] == 'n')
		return (ft_strdup("int "));
	if (specifier[0] == 'u' || specifier[0] == 'x' || specifier[0] == 'X')
		return (ft_strdup("unsigned int "));
	if (specifier[0] == 'e' || specifier[0] == 'f' || specifier[0] == 'g')
		return (ft_strdup("double "));
	if (specifier[0] == 's')
		return (ft_strdup("const char *"));
	if (specifier[0] == 'p')
		return (ft_strdup("void *"));
	else
		return (ft_strdup("void"));
}
