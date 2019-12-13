/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRF_select_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 07:23:06 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/04 04:53:35 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PRF.h"
#include "../includes/get_next_line.h"

/*
** This file will take care of building temporary files that contain on each
** line a valid combinaitions of flags. this being done for a specific
** specifier given as argument, and according to the presence of bonuses or not
**
** At maximum we can have 8 flags. we fit them inside an unsigned  char:
** bits relatively activated to a defined standard mask.
**
** note:	the flags "." and "*" are not taken in account at this stage and
** 			will be processed independently.
*/


/*
** note:	This function will creat a file containing the different possible
**			combinaitions of flags given a specifier and a set of flags.
**			First the mask is build to eliminate some unknow behaviors. this
**			is done in the subfunctions. then we copy every possibility in a
**			tmp file.
**
** note:	inputs should be the tab[0] returned by the parsing, and tba[i]
**			depending on which specifier we are working on.
**
** RETURN:	char *, the name of the file created.
**			NULL if failed
*/

char *flags_build_combinations(char *usr_flags, char *std_mask, char *specifier)
{
	unsigned char	mask;
	int				fd;
	char 			*name;
	char			*flags_reduced;

	if (!(name = create_name("../tmp_files/flags_combo_", specifier)))
		if (!failure("failed to join in flags_build_combo()"))
			return (NULL);
	if((fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644)) == -1)
		if (!failure("flags_build_combinations() failed to Open file"))
			return (NULL);
	mask = standardise_mask_flags(usr_flags, std_mask);
	mask = addapt_mask_specifier(mask, specifier);
	if (!(flags_reduced = reduce_flags_to_str(mask, STANDARD_MASK)))
		if(!failure("failed in reduce_flags_to_str()"))
			return (NULL);
	write_flags_combos(flags_reduced, fd);
	free(flags_reduced);
	close(fd);
	return (name);
}

/*
** note:	this function will name the file, according to the specifier, it
**			especially takes care of the case problem naming ...X into ..XX
**			and changing "%" into percent
**
** RETURN:	char *name_specifier
**			NULL if (failure)
*/

char *create_name(char *base_name, char *specifier)
{
	char *new_name;

	if (!(ft_strncmp(specifier, "X", 1)))
	{
		if (!(new_name = ft_strjoin(base_name, "XX")))
			return (NULL);
	}
	else if (!(ft_strncmp(specifier, "%", 1)))
	{
		if (!(new_name = ft_strjoin(base_name, "percent")))
			return (NULL);
	}
	else
	{
		if (!(new_name = ft_strjoin(base_name, specifier)))
			return (NULL);
	}
	return (new_name);
}

/*
** note:	this function will build a standardised mask depending on the
**		Ma	flags string given as argument, and of course the formated standard
**			mask that we impose in a define.
**			"-0' #+__"
**Ma
** note:	since we want to parse '.' and '*' differently we just always turn
**			them off!
**Ma
** RETURN:	unsigned char that is a mask
*/

unsigned char  standardise_mask_flags(char *flags, const char *standard_mask)
{
	unsigned char mask;
	int i;
	int k;

	i = 0;
	mask = 0;
	while (flags && flags[i])
	{
		k = 0;
		while (k <  8)
		{
			if (flags[i] == standard_mask[k])
				mask |= ((1 << 7) >>  k);
			k++;
		}
		i++;
	}
	return (mask);
}

/*
** note:	this function will addapt the mask (previsously standardised) with
**			the given specifier. so basically it turns off even more bits.
**
** RETURN:	modified mask with bits taken down when unknown behavior is met.
*/

unsigned char addapt_mask_specifier(unsigned char mask, char *spec)
{
	if (!ft_strncmp(spec, "n" , 4))
		mask &= ~(F_MINU);
	if (!ft_strncmp(spec, "c", 4) || !ft_strncmp(spec, "s", 4) \
		|| !ft_strncmp(spec, "p", 4) || !ft_strncmp(spec, "n", 4))
		mask &= ~(F_ZERO);
	if (!ft_strncmp(spec, "c", 4) || !ft_strncmp(spec, "s", 4) \
		|| !ft_strncmp(spec, "p", 4) || !ft_strncmp(spec, "x", 4) \
		|| !ft_strncmp(spec, "llx", 4) || !ft_strncmp(spec, "lx", 4) \
		|| !ft_strncmp(spec, "hhx", 4) || !ft_strncmp(spec, "hx", 4) \
		|| !ft_strncmp(spec, "X", 4) || !ft_strncmp(spec, "e", 4) \
		|| !ft_strncmp(spec, "n", 4))
		mask &= ~(F_APPO);
	if (!ft_strncmp(spec, "c", 4) || !ft_strncmp(spec, "s", 4) \
		|| !ft_strncmp(spec, "p", 4) || !ft_strncmp(spec, "u", 4) \
		|| !ft_strncmp(spec, "llu", 4) || !ft_strncmp(spec, "lu", 4) \
		|| !ft_strncmp(spec, "hhu", 4) || !ft_strncmp(spec, "hu", 4) \
		|| !ft_strncmp(spec, "x", 4) || !ft_strncmp(spec, "X", 4) \
		|| !ft_strncmp(spec, "llx", 4) || !ft_strncmp(spec, "lx", 4) \
		|| !ft_strncmp(spec, "hhx", 4) || !ft_strncmp(spec, "hx", 4) \
		|| !ft_strncmp(spec, "n", 4))
		mask &= ~(F_SPAC | F_PLUS);
	if (!ft_strncmp(spec, "c", 4) || !ft_strncmp(spec, "s", 4) \
		|| !ft_strncmp(spec, "p", 4) || !ft_strncmp(spec, "d", 4) \
		|| !ft_strncmp(spec, "i", 4) || !ft_strncmp(spec, "u", 4) \
		|| !ft_strncmp(spec, "lli", 4) || !ft_strncmp(spec, "li", 4) \
		|| !ft_strncmp(spec, "hhi", 4) || !ft_strncmp(spec, "hi", 4) \
		|| !ft_strncmp(spec, "llu", 4) || !ft_strncmp(spec, "lu", 4) \
		|| !ft_strncmp(spec, "hhu", 4) || !ft_strncmp(spec, "hu", 4) \
		|| !ft_strncmp(spec, "n", 4))
		mask &= ~(F_HASH);
	return (mask);
}

/*
** note:	once all the parsing has been done on the user input and the bits
**			have been deactivated according to the current specifier case, we
**			reduce the flags present to the shortest string. the order does not
**			matter. it will then be sent to the function that use a binary
**			counter to find all combinaitions.
**
** note: 	we know we won't find any activated bits from 64 bit weight. ->6
**			we know the length of the string is 8, so we start at index 7. ->7
**
** RETURN:	char *str
**			NULL if failed.
*/

char *reduce_flags_to_str(unsigned char mask, char *std_flags)
{
	char *str;
	int i;
	char flags[8] = {'\0'};
	int j;

	i = 0;
	j = -1;
	while (i < 6)
	{
		if ((1 << i) & mask)
			flags[++j] = std_flags[7 - i];
		i++;
	}
	if (!(str = ft_strdup(flags)))
		return (NULL);
	return (str);
}

/*
** note:	this function will write flag combos into a file. it uses a binary
**			counter technic.
**
** note2:	we will discard the warnings produces between '0' and '-', AND
**			between ' ' and '+'.**
**
** RETURN:	1 if OK
**			0 if failure
*/

int		write_flags_combos(char *flags, int fd)
{
	int i;
	int k;
	char line[10] = {'\0'};
	int j;
	int lim;
	int len;

	len = -1;
	lim = 1;
	while (flags[++len])
		lim *= 2;
	i = -1;
	while (++i < lim)
	{
		k = -1;
		while (line[++k])
			line[k] = '\0';
		k = -1;
		j = -1;
		while (++k < len)
			if ((1 << k) & i) //flag presence detected
				line[++j] = flags[k];
		if (parse_flags_comb_for_warnings(line))
			ft_putendl_fd(line, fd);
	}
	return (0);
}

/*
** note:	this function prevents from keeping the flag combinations that will
**			produce a warning:
**			'+' and ' '
**			'0' and '-'
**
** RETURN:	1 if not warning detected, else 0
*/

int		parse_flags_comb_for_warnings(char *line)
{
	if ((ft_strchr(line, ' ') && ft_strchr(line, '+')) \
				|| ((ft_strchr(line, '0') && ft_strchr(line, '-'))))
		return (0);
	return (1);
}
