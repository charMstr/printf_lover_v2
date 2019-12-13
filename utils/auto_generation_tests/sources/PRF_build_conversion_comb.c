/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRF_build_conversion_comb.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 13:10:52 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/03 04:24:03 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PRF.h"
#include "../includes/get_next_line.h"

/*
** this file will take care of building a file containing on each line every
** combinations of conversion specification within a chosen range for padding
** and precision.
**
** note:	precision cannot be negative.
**			both brecision and padding can be an empty string.
**			"." is not allowed for c, p and n specifiers. therefore we cannot
**			have two stars for this case.
*/

/*
** note:	this function will be the root of the buiding of the temporary file
**			containing on every lines a possible combination of conversion
**			specifications.
**
** RETURN:	a file name that was just created.
**			NULL if failed
*/

char *conversion_spec_build_comb(char *specifier, int range)
{
	int		fd_w;
	char	*file_name;

	if (!(file_name = create_name("../tmp_files/conversions_combo_", specifier)))
		if (!(failure("failed to join in conversion_spec_build_comb(")))
			return (NULL);
	if ((fd_w = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644)) == -1)
		if (!(failure("failed to open/creat file in conversion_spec_build_comb(")))
			return (NULL);
	if (!(ft_strncmp(specifier , "p", 4)) || !(ft_strncmp(specifier, "s", 4)))
		range *= 4;
	if (!(make_padding(specifier, fd_w, range)))
		return (NULL);
	close(fd_w);
	return (file_name);
}

/*
** note:	this function will creat the different combinations for padding
**			within the range given as argument. after printing it in a file,
**			everytime on a different line, we will call the function that will
**			add precision on each line.
**
** note:	'nothing', and '*' will be introduced at some stage.
**
** RETURN:	1 everything ok
**			0 ko
*/

int	make_padding(char *specifier, int fd_w, int range)
{
	int i;
	char *number;

	i = -range - 1;
	while (++i <= range  + 2)
	{
		if (i == 0)
			number = ft_strdup("");
		else if (i == 1)
			number = ft_strdup("*");
		else if (i > 0)
			number = ft_itoa(i - 2);
		else
			number = ft_itoa(i);
		if (!number)
			return (failure("fail in make_padding()"));
		if (!(make_precision(number, specifier, fd_w, range)))
		{
			free(number);
			return (failure("fail in make_precision()"));
		}
		ft_putendl_fd(number, fd_w);
		free(number);
	}
	return (1);
}

/*
** note:	this function will prepare the work for creating the precision and
**			append it to the padding previously made and given as argument.
**			first we add a dot , and keep going only if we dont meet a special
**			case.
**
** note:	special cases for c, p , n... we will only print a ".', one time
**			out of two.
**
** RETURN:	1 ok
**			0 KO
*/

int	make_precision(char *padding, char *specifier, int fd_w, int range)
{
	char *str;

	if (!(str = ft_strjoin(padding, ".")))
		return (0);
	if ((!ft_strncmp(specifier, "p", 3) || !ft_strncmp(specifier, "c", 3) \
		|| !ft_strncmp(specifier, "n", 3)))
	{
		ft_putendl_fd(str, fd_w);
		free(str);
		return (1);
	}
	if (ft_strncmp(specifier, "n", 2))
		if (!make_precision2(str, fd_w, range))
		{
			free(str);
			return (0);
		}
	free(str);
	return (1);
}

/*
** note:	this funcion will add precision to a string already containing the
** 			"."
**
** RETURN:	1 if ok
**			0 f failed
*/

int make_precision2(char *padding, int fd_w, int range)
{
	int i;
	char *number;
	char *itoa_str;

	i = -1;
	while (++i <= range  + 2)
	{
		if (i == 0)
			number = ft_strjoin(padding, "");
		else if (i == 1)
			number = ft_strjoin(padding, "*");
		else
		{
			if (!(itoa_str = ft_itoa(i - 2)))
				return (0);
			number = ft_strjoin(padding, itoa_str);
			free(itoa_str);
		}
		if (!number)
			return (failure("fail in make_precision2()"));
		ft_putendl_fd(number, fd_w);
		free(number);
	}
	return (1);
}
