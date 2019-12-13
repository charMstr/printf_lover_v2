/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRF_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:41:01 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/29 17:25:50 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PRF.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (write(fd, s, ft_strlen(s)) == -1)
		write(2, s, ft_strlen(s));
}

void	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		write(2, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	char c;

	c = '\n';
	if (!s)
		return ;
	if (write(fd, s, ft_strlen(s)) == -1)
	{
		write(2, s, ft_strlen(s));
		write(2, &c, 1);
	}
	else
		write(fd, &c, 1);
}

int success_endl(char *str)
{
	success(str);
	ft_putchar_fd('\n', 1);
	return (1);
}

int success(char *str)
{
	ft_putstr_fd(GREEN, 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(CLEAR, 1);
	return (1);
}

int	failure(char *str)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(CLEAR, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

void print_separator(void)
{
	write(1, "\n-------------------------------------------------------------------------------\n", 82);
}

void introduce_test(char *name)
{
	print_separator();
	ft_putstr_fd("test for: ", 1);
	ft_putstr_fd(name, 1);
	print_separator();
}

