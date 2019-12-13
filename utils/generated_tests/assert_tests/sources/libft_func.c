/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRF_libft_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:44:35 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/09 17:58:09 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf_lover_test_func.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (write(fd, s, ft_strlen(s)) == -1)
		write(2, s, ft_strlen(s));
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	i = 0;
	len = ft_strlen(s1);
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

void	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		write(2, &c, 1);
}

int	failure(char *str)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(CLEAR, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (!n)
		return (0);
	while ((s1[i] == s2[i]) && s1[i] && s2[i] && (i + 1 < n))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n < -9)
			ft_putnbr_fd((-1 * (n / 10)), fd);
	}
	else if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	(n > 0) ? ft_putchar_fd(n % 10 + '0', fd)
		: ft_putchar_fd(-(n % 10) + '0', fd);
}
