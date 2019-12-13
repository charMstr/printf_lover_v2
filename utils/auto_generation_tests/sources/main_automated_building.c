/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_comb_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 01:10:38 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/13 14:54:23 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PRF.h"
#include "../includes/get_next_line.h"

int	main(void)
{
	char	*file_tmp;
	char	**tab;
	int		i;
	int		fd_mk;

	if (!(tab = finish_parsing(BASIC_FLA, BASIC_SPE)))
		return (failure("failed in finish_parsing()"));
	if ((fd_mk = open(FILE_MK, O_CREAT | O_RDWR | O_TRUNC, 0644)) == -1)
		return (0);
	i = 0;
	while (tab[++i])
	{
		if(!(file_tmp = build_tmp_files(tab[0], STANDARD_MASK, tab[i], RANGE)))
		{
			close(fd_mk);
			free_double_dim_array(tab, ft_strlen_2d_array(tab));
			return (failure("create_tmp_files failed in main"));
		}
		if (!(build_function_files(file_tmp, tab[i], NORMAL_TEST)))
		{
			close(fd_mk);
			free_double_dim_array(tab, ft_strlen_2d_array(tab));
			free(file_tmp);
			return (failure("failed to creat function file in main"));
		}
		if (!(build_function_files(file_tmp, tab[i], ASSERT_TEST)))
		{
			close(fd_mk);
			free_double_dim_array(tab, ft_strlen_2d_array(tab));
			free(file_tmp);
			return (failure("failed to creat function file in main"));
		}
		if (!(update_mk_file(fd_mk, tab[i], file_tmp)))
		{
			close(fd_mk);
			free_double_dim_array(tab, ft_strlen_2d_array(tab));
			free(file_tmp);
			return (failure("failed to update .mk file in main"));
		}
		free(file_tmp);
	}
	close(fd_mk);
	free_double_dim_array(tab, ft_strlen_2d_array(tab));
	return (0);
}
