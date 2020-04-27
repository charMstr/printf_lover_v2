/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 07:11:23 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/09 17:19:19 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"
#include <stdlib.h>

int	main(int argc __attribute__((unused)), char *argv[])
{
	int	i;
	int *p;
//	int		tab[7] = {-135, -12, -1, 0, 1, 13, 198};

	i = atoi(argv[1]);
	p = &i;
	p = NULL;
	printf("-->|%-16.p|<--\n", p);
	return (0);
}
