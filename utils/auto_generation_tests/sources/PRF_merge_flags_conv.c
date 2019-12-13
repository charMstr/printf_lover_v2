/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRF_merge_flags_conv.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 20:02:43 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/03 04:35:08 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PRF.h"
#include "../includes/get_next_line.h"

/*
** note:	this file will be merging the file created in subfunctions.
**			for a given specifier, a flags file is created, then a convertion
**			specifications file, then we build all possible combinations.
*/

/*
** note:	this function will make a file that contains all flags, and spec
**			possible combinations within a range for variation of padding and
**			precisions.
**
** RETURN:	char *, the name of the file created
**			NULL if it failed.
*/

char *merge_flags_conv(char *flags, char* std_mask,char *specifier, int range)
{
	char *file_flags;
	char *file_conv;
	char *combo;

	if (!(file_flags = flags_build_combinations(flags, std_mask, specifier)))
		if (!(failure("failure in flags_buid_combinations")))
			return (NULL);
	if (!(file_conv = conversion_spec_build_comb(specifier, range)))
		if (!(failure("failure in conversion_spec_build_comb()")))
		{
			free(file_flags);
			return (NULL);
		}
	if (!(combo = merge_flags_conv_assist(file_flags, file_conv, specifier)))
		if (!(failure("failure in merge_flags_conv_assist()")))
		{
			free(file_flags);
			free(file_conv);
			return (NULL);
		}
	free(file_flags);
	free(file_conv);
	return (combo);
}

/*
** note:	this function will take care of opening all the file descriptors
**			before actually merging the files.
**
** RETURN:	char *name of file if success
**			NULL if failure
*/

char *merge_flags_conv_assist(char *file1, char *file2, char *specifier)
{
	char *combo_file;
	int fd_r1;
	int fd_w;

	if (!(combo_file = create_name("../tmp_files/combo_", specifier)))
		if (!(failure("failed to join in merge_flags_conv_assist()")))
			return (NULL);
	if ((fd_r1 = open(file1, O_RDONLY)) == -1)
	{
			free(combo_file);
			return (NULL);
	}
	if ((fd_w = open(combo_file, O_CREAT | O_RDWR | O_TRUNC, 0644)) == -1)
	{
			close(fd_r1);
			free(combo_file);
			return (NULL);
	}
	if (!(merge_for_real_the_f_files(fd_r1, fd_w, file2, specifier)))
		if (!(failure("failed in merge_for_real_the_f_files(")))
		{
			close(fd_r1);
			close(fd_w);
			free(combo_file);
			return (NULL);
		}
	close(fd_r1);
	close(fd_w);
	return (combo_file);
}

/*
** note:	this function will merge the files 1 and 2 in every possible
**			combinations into the fd_w, (file to be written)
**
** RETURN:	1 ok
**			0 KO
*/

int	merge_for_real_the_f_files(int fd1, int fd_w, char *file2_name, \
		char *specifier)
{
	int	fd2;
	char *line1;
	char *line2;
	char *new;

	while (get_next_line(fd1, &line1))
	{
		if ((fd2= open(file2_name, O_RDONLY)) == -1)
		{
			free(line1);
			return (failure("failed to opeN in merge_for_real_the_f_files()"));
		}
		while (get_next_line(fd2, &line2))
		{
			if (!(new = ft_strjoin(line1, line2)))
			{
				free(line1);
				free(line2);
				close(fd2);
				return (failure("failed to join in merge_for_real_the_f_files()"));
			}
			if (check_for_warning_introductions(new, specifier))
				ft_putendl_fd(new, fd_w);
			free(new);
			free(line2);
		}
		close(fd2);
		free(line1);
	}
	return (1);
}

/*
** note:	this function will check if there is any anoying combination
**			with a negative signed padding number and a zero flag.
**
** note:	the case between the negative flag and the zero padding number has
**			is being taken care of as well, so is the case fo the unknown
**			behavior when we try to put a negative padding with "c" "s" "p"
**			and "n" (except for a star "*" substitution)
**
** RETURN:	1 if (ok to print)
**			0 if (need to discard line)
*/

int	check_for_warning_introductions(char *new, char *specifier)
{
	int i;
	int found_z;
	int found_m;
	int	unknown_b;

	found_z = 0;
	found_m = 0;
	unknown_b = 0;
	i = -1;
	if (!(ft_strncmp(specifier, "n", 1)) || !(ft_strncmp(specifier, "c", 1))\
		|| !(ft_strncmp(specifier, "s", 1)) || !ft_strncmp(specifier, "p", 1))
		unknown_b = 1;
	while (new[++i])
	{
		if (new[i] == '0')
			found_z = 1;
		if (new[i] == '-')
			found_m = 1;
		if (found_z && (found_m || unknown_b))
			return (0);
		if (new[i] == '.')
			break;
	}
	return (1);
}
