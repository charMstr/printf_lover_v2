/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:00:43 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/13 19:00:45 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf_lover_test_func.h"

size_t	my_ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	my_ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (write(fd, s, my_ft_strlen(s)) == -1)
		write(2, s, my_ft_strlen(s));
}

char	*my_ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	i = 0;
	len = my_ft_strlen(s1);
	if (!(ptr = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
	{
		*(ptr + i) = *(s1 + i);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}

void	my_ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		write(2, &c, 1);
}

int	failure(char *str)
{
	my_ft_putstr_fd(RED, 2);
	my_ft_putstr_fd(str, 2);
	my_ft_putstr_fd(CLEAR, 2);
	my_ft_putchar_fd('\n', 2);
	return (0);
}

int	my_ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (!n)
		return (0);
	while ((s1[i] == s2[i]) && s1[i] && s2[i] && (i + 1 < n))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	my_ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		my_ft_putchar_fd('-', fd);
		if (n < -9)
			my_ft_putnbr_fd((-1 * (n / 10)), fd);
	}
	else if (n > 9)
		my_ft_putnbr_fd(n / 10, fd);
	(n > 0) ? my_ft_putchar_fd(n % 10 + '0', fd)
		: my_ft_putchar_fd(-(n % 10) + '0', fd);
}
