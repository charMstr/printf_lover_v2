/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRF_automated_building_assist_main.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 03:24:26 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/08 23:19:32 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/PRF.h"
#include "../includes/get_next_line.h"

/*
** note:	this function will build temporary file.
**
** RETURN:	char *name of .c file.
**			NULL if (failure)
*/

char *build_tmp_files(char *flags, char *std_mask, char *specifier, int range)
{
	char *file1;
	char *file2;

	if (!std_mask || !specifier || !flags)
		return (NULL);
	if (!(file1 = merge_flags_conv(flags, std_mask, specifier, range)))
		if(!(failure("failed to merge flags and conv_specs in create_tmp_files")))
			return (NULL);
	if (!(file2 = build_printf_file(file1, specifier, range)))
	{
		free(file1);
		failure("failed to creat file with printf calls in create_tmp_files");
		return (NULL);
	}
	free(file1);
	return (file2);
}

/*
** note:	this function will build a .mk file that will be used to update
**			two variables which will later-on be imported into the master
**			makefile for compilation configurations.
**
** note:	basically if a -D SPECIFIER_<something> is defined it will be
**			preprocessed in the main and the #ifdef section will be compiled.
**			the main can then contain every functions even if not even present/
**			built in such a way.
**
** note: 	SRC_FILE variable will be updated with the sources built as we go.
**
** RETURN:	1 if (ok)
**			0 if (failure)
*/

int	update_mk_file(int fd_mk, char *specifier, char *name)
{
	static int	opened;
	char		*new_str;
	char		*basename;

	if (!specifier)
		return (0);
	if (!(new_str = modify_specifier_for_mk_file(specifier)))
		return (0);
	if (!(basename = ft_strrchr(name, '/')))
		return (0);
	if (!opened)
	{
		ft_putstr_fd("SPECIFIER := -D SPECIFIER_", fd_mk);
		ft_putendl_fd(new_str, fd_mk);
		ft_putstr_fd("SRC_FILES := main_call_test_funcs libft_func ", fd_mk);
		ft_putendl_fd(basename + 1, fd_mk);
		++opened;
	}
	else
	{
		ft_putstr_fd("SPECIFIER := $(SPECIFIER) -D SPECIFIER_", fd_mk);
		ft_putendl_fd(new_str, fd_mk);
		ft_putstr_fd("SRC_FILES := $(SRC_FILES) ", fd_mk);
		ft_putendl_fd(basename + 1, fd_mk);
	}
	free(new_str);
	return (1);
}

/*
** note:	this function will modify the specifier for naming the -D option
**			that will be sent to gcc
**
** note2:	% becomes PERCENT
**			X becomes XX
**			all letters are being uppercased
**
** RETURN:	char *specifier_adapted
**			NULL if (failure)
*/

char *modify_specifier_for_mk_file(char *specifier)
{
	int i;

	i = -1;
	if (!ft_strncmp(specifier, "X", 1))
		return (ft_strdup("XX"));
	else if (!ft_strncmp(specifier, "%", 1))
		return (ft_strdup("PERCENT"));
	else
	{
		while (specifier[++i])
			specifier[i] = ft_toupper(specifier[i]);
		return (ft_strdup(specifier));
	}
	return (NULL);
}
