/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRF_parsing_inputs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 02:35:59 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/01 23:55:42 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PRF.h"
#include "../includes/get_next_line.h"

/*
** note:	this file contains all the functions needed to parse the inputs
**			the user will be requested in the command line at the very
**			beggining of the run of the program. it is going to be used for
**			customizing the tests, building or not .c files according to the
**			bonuses the user wants to attempt.
*/

/*
** note:	this function will simply ask for a specific matter, and a specific
**			non_bonus part of the subject, if you want to add a specific bonus
**			part to whats going to be build/tested later on
*/

void	ask_for_the_matter(char *matter, char *subject_basic, char *subject_bonus, int option)
{
	ft_putstr_fd("\nconfiguring the ", 1);
	ft_putstr_fd(matter, 1);
	ft_putstr_fd(" that will be tested:\n", 1);
	ft_putstr_fd("if you want to, add some bonus ", 1);
	ft_putstr_fd(matter, 1);
	if (!option)
	{
		ft_putstr_fd(" to the existing: \"", 1);
		ft_putstr_fd(subject_basic, 1);
		ft_putchar_fd('\"', 1);
	}
	ft_putstr_fd("\n--> select from: \"", 1);
	ft_putstr_fd(subject_bonus, 1);
	ft_putchar_fd('\"',  1);
	if (option)
		ft_putstr_fd(" adding 1 underscore in between each flags,", 1);
	ft_putendl_fd(" then press enter:\n", 1);
}

/*
** note:	this fucntion will simply ask for confirmation on screen
*/

void	ask_confirmation(char *matter, char *line)
{
	if (!matter || !line)
		return ;
	ft_putstr_fd("do you confirm the following extra ", 1);
	ft_putstr_fd(matter, 1);
	ft_putstr_fd("? \"", 1);
	success(line);
	ft_putstr_fd("\"\n", 1);
	ft_putstr_fd("y or Y for yes then enter: ", 1);
}

/*
** note:	this function is speciffically designed to parse the "l_ll_h_hh"
**			extra flags
**
** RETURN:	1 if ok
**			0 if ko
*/

int	parse_extra_flags(char *line, char *subject_bonus)
{
	int		i;
	char	present;
	char	position;
	char	*res;
	char	underscore;

	if (!line || !subject_bonus)
		return (0);
	i = 0;
	present = 0;
	underscore = 0;
	if (line[0] == '_' || ft_strlen(line) > 9)
		return (failure("string cant start by a '_' or string too long, not possible"));
	while (line[i])
	{
		if (!(res = ft_strchr(subject_bonus, line[i])))
			return (failure("character impossible, refer to prompt for available inputs"));
		if (line[i] == '_')
		{
			underscore++;
			if (underscore > 1)
				return (failure("sorry, can't have two '_' in a raw"));
		}
		else
		{
			if (line[i] == line[i + 1])
			{
				if (line[i + 1] && line[i + 2] && line[i + 1] == line[i + 2])
					return (failure("too many lll or hhh"));
				position = res - subject_bonus + 1;
				if ((present & (1 << position)) == (1 << position))
					return (failure("same flag entered twice"));
				present |= (1 << position);
				i++;
			}
			else
			{
				position = res - subject_bonus;
				if ((present & (1 << position)) == 1)
					return (failure("same flag entered twice"));
				present |= (1 << position);
			}
			if (underscore)
				underscore--;
		}
		i++;
	}
	if (i > 0  && (line[i - 1] == '_'))
		return (failure("string can't end by a '_'"));
	return (1);
}

/*
** note:	this function will test the user_input string against the original
**			subject option, and against the bonus offers, and chek it matches
**			and doesn't contains duplicates.
**
** note:	the choice of filling in anything is considered valid. no bonuses!
**
** RETURN:	1 if ok
**			0 if KO
*/

int parse_for_mistakes(char *user_input, char *subject_basic, char *subject_bonus)
{
	int		i;
	char	present;
	char	*res;
	int		position;

	if (!user_input || !subject_basic || !subject_bonus)
		return (0);
	present = 0;
	i = 0;
	while (user_input[i])
	{
		if (ft_strchr(subject_basic, user_input[i]))
			return (failure("character was already part of the basic subject"));
		if ((res = ft_strchr(subject_bonus, user_input[i])))
		{
			position = res - subject_bonus;
			if ((present & (1 << position)) == 0)
				present |= (1 << position);
			else
				return (failure("character typed in twice"));
		}
		else
			return (failure("a character was not part of the options offered..."));
		i++;
	}
	return (1);
}

/*
** note:	this function will prompt a question at the very beginning of the
**			user exp. it wil be called three times and try to update or not the
**			original flags, and convertion specifier, with bonus
**			check that the answer given are within the 42 project range.
**			prompt example: do you want to add bonus flags?
**
** RETURN:	char * if ok
**			NULL if failed.
*/

char	*parse_user_input_matter(char *matter, char *subject_basic, char *subject_bonus, int option)
{
	char	valid;
	char	*line;
	char	*line_conf;
	int		fd1;

	if ((fd1 = open("/dev/stdin", O_RDONLY)) == -1)
	{
		failure("failed to open the stdin in parse_user_input_matter()");
		return (NULL);
	}
	valid = 0;
	line = NULL;
	while (!valid)
	{
		free(line);
		ask_for_the_matter(matter, subject_basic, subject_bonus, option);
		get_next_line(fd1, &line);
		get_next_line(fd1, NULL);
		ft_putstr_fd("\033[1A\033[J", 1);
		if ((!(option) && parse_for_mistakes(line, subject_basic, subject_bonus))
				|| (option && parse_extra_flags(line, subject_bonus)))
		{
			ask_confirmation(matter, line);
			get_next_line(fd1, &line_conf);
			get_next_line(fd1, NULL);
			ft_putstr_fd("\033[1A\033[J", 1);
			if (line_conf[0] == 'y' || line_conf[0] == 'Y')
				valid ^= 1;
			else
				failure("NO!");
			free(line_conf);
		}
		else
			failure(line);
	}
	success_endl("OK");
	return (line);
}
