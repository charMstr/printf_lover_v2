/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRF_parsing_inputs2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 13:41:53 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/29 13:44:40 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PRF.h"

/*
** note:	this function will join at char **tab with another.
**
** RETURN:	char **tab if success
**			NULL if failure occur
*/

char **ft_join_splits(char **tab1, char **tab2)
{
	char **new;
	int j;
	int k;
	int i;

	j = -1;
	k = -1;
	while (tab1[++j]);
	while (tab2[++k]);
	if (!(new = (char **)malloc(sizeof(char *) * (j + k + 1))))
		return (NULL);
	new[j + k] = NULL;
	i = 0;
	while (i < j + k)
	{
		if (i < j)
			new[i] = ft_strdup(tab1[i]);
		else
			new[i] = ft_strdup(tab2[i - j]);
		i++;
	}
	return (new);
}

/*
** note:	this function will insert a character in between every char in a
**			string in order to make it splitable. if reused, it should always
**			be checked at first that the given character is not present in the
**			string.
**
** RETURN:	char * with c in between each char;
**			NULL if failure
*/

char *make_splitable(char *str, char c)
{
	int i;
	int j;
	char *new;

	j = ft_strlen(str);
	i = j;
	if (j > 1)
		i = 2 * j - 1;
	if (!(new = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	new[i] = '\0';
	while (--i >= 0)
	{
		if (i % 2 != 0)
			new[i] = c;
		else
			new[i] = str[--j];
	}
	return (new);
}

/*
** note:	this function will prepend a char * at the beginning of a
**			char **tab. and return a fully new malloced copy of char **tab.
**
** RETURN:	char **newtab
**			NULL if failure
*/

char **prepend_chartab(char *str, char **tab)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	if (!str || !tab)
		return (NULL);
	while (tab[i])
		i++;
	i++;
	if (!(new = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	new[i] = NULL;
	new[0] = ft_strdup(str);
	j = 1;
	while (j < i)
	{
		new[j] = ft_strdup(tab[j - 1]);
		j++;
	}
	return (new);
}

/*
** note:	this function is just here for good practice, ti will clean the
**			memory in case of failure of the get_user_choice();
**			or aggregate_bonus_and_subject();
**
** RETURN:	NULL
*/

void *free_double_dim_array(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		tab[i] = NULL;
		i--;
	}
	free(tab);
	return (NULL);
}

/*
** note:	this function should be used in order to assist the function that
**			frees the memory of double dimensions arrays.
**
** RETURN:	size of the double dimension array;
*/

int	ft_strlen_2d_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
