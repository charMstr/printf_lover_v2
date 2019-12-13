/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_lover_test_func.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:00:12 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/13 19:00:14 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_LOVER_TEST_FUNC_H
# define PRINTF_LOVER_TEST_FUNC_H

# include <assert.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define RED "\033[38;5;1m"
# define CLEAR "\033[0m"

void	my_ft_putstr_fd(char *s, int fd);
size_t	my_ft_strlen(const char *s);
void	my_ft_putchar_fd(char c, int fd);
int		failure(char *str);
char	*my_ft_strdup(const char *s1);
int		my_ft_strncmp(const char *s1, const char *s2, size_t n);
void	my_ft_putnbr_fd(int n, int fd);

int		test_func_c(int c);
int		test_func_s(const char *s);
int		test_func_p(void *p);
int		test_func_d(int d);
int		test_func_i(int i);
int		test_func_u(unsigned int u);
int		test_func_x(unsigned int x);
int		test_func_X(unsigned int X);
int     test_func_percent(void);

int		test_func_n(int n);
int		test_func_f(double f);
int		test_func_g(double g);
int		test_func_e(double e);

int     test_func_hi(short int hi);
int     test_func_hx(short int hx);
int     test_func_hu(short int hu);
int     test_func_hhi(signed char hhi);
int     test_func_hhx(signed char hhx);
int     test_func_hhu(signed char hhu);

int     test_func_li(long int li);
int     test_func_lx(long int lx);
int     test_func_lu(long int lu);
int     test_func_lli(long long int lli);
int     test_func_llx(long long int llx);
int     test_func_llu(long long int llu);

#endif
