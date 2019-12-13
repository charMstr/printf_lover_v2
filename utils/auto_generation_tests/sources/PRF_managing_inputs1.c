/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRF_managing_inputs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 07:27:51 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/01 23:53:35 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PRF.h"

/*
** note:	this file contains the functions that will manage the inputs from
**			the user used to configure the automated creation of c files.
**			subfunctions are stored into PRF_parsing_inputs.c
**
**			the result will handle to the Main a char **tab that contains:
**			tab[0] ==> flags;
**			then all the different conversions specifiers a short strings;
*/


/*
** note:	this fucntion is the root of the parsing.
**
** RETURN:	char **tab containing the flags at address zero, and all the
**			different combinaitions of specifiers until the end;
**			NULL if (failure)
*/

char	**finish_parsing(char *basic_flags, char *basic_specifiers)
{
	char	**returned_tab;
	char	**tab1;
	char	**tab2;
	char	**tab3;

	if (!(returned_tab = aggregate_bonus_and_subject(basic_flags, basic_specifiers)))
		return (NULL);
	if (!(tab1 = split_specifiers(returned_tab[1])))
		return (free_double_dim_array(returned_tab, 3));
	if (ft_strlen(returned_tab[2]))
	{
		if (!(tab2 = build_combinaitions_from_extra_flags(returned_tab[2])))
		{

			free_double_dim_array(tab1, ft_strlen_2d_array(tab1));
			return (free_double_dim_array(returned_tab, 3));
		}
		if (!(tab3 = ft_join_splits(tab1, tab2)))
		{
			free_double_dim_array(tab2, ft_strlen_2d_array(tab2));
			free_double_dim_array(tab1, ft_strlen_2d_array(tab1));
			return (free_double_dim_array(returned_tab, 3));
		}
		free_double_dim_array(tab2, ft_strlen_2d_array(tab2));
		free_double_dim_array(tab1, ft_strlen_2d_array(tab1));
		if (!(tab2 = prepend_chartab(returned_tab[0], tab3)))
		{
			free_double_dim_array(tab3, ft_strlen_2d_array(tab3));
			return (free_double_dim_array(returned_tab, 3));
		}
		free_double_dim_array(tab3, ft_strlen_2d_array(tab3));
		free_double_dim_array(returned_tab, 3);
		return (tab2);
	}
	if (!(tab2 = prepend_chartab(returned_tab[0], tab1)))
	{
		free_double_dim_array(tab1, ft_strlen_2d_array(tab1));
		return (free_double_dim_array(returned_tab, 3));
	}
	free_double_dim_array(tab1, ft_strlen_2d_array(tab1));
	free_double_dim_array(returned_tab, 3);
	return (tab2);
}

/*
** note:	this function will non-smartly build just a couple of chosen
**			combinations with the extra bonus flags. l, ll, h, hh will each
**			be combinated with i , u, x so if all 4 bonus are here, it will add
**			12 more path, 12 more test_test_functions to be created.
**			ex: of input strings: "l" or "hh" or "l_hh"
**
** note2:	we know we will have always at least one char, and always one more
**			char than '_', that is why size starts at one.
**
** RETURN:	NULL if failed
**			a char ** tab containing each strings.
*/

char **build_combinaitions_from_extra_flags(char *extra_bonus)
{
	int	i;
	char **new;
	char **tmp;
	int j;
	int k;

	i = -1;
	if (!(tmp = ft_split(extra_bonus, '_')))
		return (NULL);
	while (tmp[++i])
		;
	if (!(new = (char**)malloc(sizeof(char *) * (i * 3 + 1))))
		return (free_double_dim_array(tmp, i));
	new[i * 3] = NULL;
	j = -1;
	k = -1;
	while (++j < i * 3)
	{
		if(!(new[j++] = ft_strjoin(tmp[++k], "i")))
		{
			free_double_dim_array(new, j--);
			return (free_double_dim_array(tmp, i));
		}
		if (!(new[j++] = ft_strjoin(tmp[k], "x")))
		{
			free_double_dim_array(new, j--);
			return (free_double_dim_array(tmp, i));
		}
		if (!(new[j] = ft_strjoin(tmp[k], "u")))
		{
			free_double_dim_array(new, j);
			return (free_double_dim_array(tmp, i));
		}
	}
	free_double_dim_array(tmp, i);
	return (new);
}

/*
** note:	this function will render the string splitable, using
**			make_splitable(), then split it with ft_split;
**
** RETURN:	char ** if success,
**			NULL if failure
*/

char **split_specifiers(char *specifiers)
{
	char *tmp;
	char **tab;

	if (!specifiers)
		return (NULL);
	if (!(tmp = make_splitable(specifiers, '_')))
		return (NULL);
	if (!(tab = ft_split(tmp, '_')))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (tab);
}

/*
** note:	this function will collect the user's input at the very beggining
**			of this printf_lover experience, this will be used to configure
**			the rest of the program and build tests according to those choices.
**
** RETURN:	char **tab containing in	tab[0] chosen extra flags
**										tab[1] chosen conversions specifiers
**										tab[2] the extra flags or ""
**			NULL if failure
*/

char **get_user_choices(char *basic_flags, char *basic_specifiers)
{
	char **tab;

	if (!(tab = (char **)malloc(sizeof(char *) * (3 + 1))))
		return (NULL);
	tab[3] = NULL;
	if (!(tab[0] = parse_user_input_matter("flags", basic_flags, "'# +", 0)))
		return (free_double_dim_array(tab, 0));
	if (!(tab[1] = parse_user_input_matter("conversion specifiers", \
					basic_specifiers, "nfge", 0)))
		return (free_double_dim_array(tab, 1));
	if (!(tab[2] = parse_user_input_matter("extra flags", "", "l_ll_h_hh", 1)))
		return (free_double_dim_array(tab, 2));
	return (tab);
}

/*
** note:	this function will collect the user's bonus choices with
**			get_user_choice() and join those choices with the mandatory part
**			of the 42 subject.
**
** RETURN:	char **
**			NULL if failure
*/

char **aggregate_bonus_and_subject(char *basic_flag, char *basic_specifier)
{
	char **tab;
	char *tmp;

	if (!(tab = get_user_choices(basic_flag, basic_specifier)))
		return (NULL);
	tmp = tab[0];
	if (!(tab[0] = ft_strjoin(basic_flag, tab[0])))
		return (free_double_dim_array(tab, 3));
	free(tmp);
	tmp = tab[1];
	if (!(tab[1] = ft_strjoin(basic_specifier, tab[1])))
		return (free_double_dim_array(tab, 3));
	free(tmp);
	return (tab);
}

