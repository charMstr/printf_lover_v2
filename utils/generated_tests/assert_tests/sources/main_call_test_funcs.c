/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_call_test_funcs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 05:33:41 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/09 18:15:24 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf_lover_test_func.h"

int	main(int argc, char *argv[])
{
	char	*ptr_char;
	char 	*dummy_ptr1;
	char 	*dummy_ptr2;
	int		i;
	int		tab[7] = {-135, -12, -1, 0, 1, 13, 198};

	dummy_ptr1 = (char *)0x7f93b1402710;
	dummy_ptr2 = (char *)0x0093b1402710;
	if (argc != 2)
	{
		failure("need to provide 1 arg");
		return (0);
	}
	if (!ft_strncmp(argv[1] , "exit", 4))
		return (0);
	i = -1;
	if ((argv[1][0] == 'c') || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_c(tab[i]);
	if ((argv[1][0] == 's') || !ft_strncmp(argv[1] , "all", 3))
	{
		ptr_char = ft_strdup("abc");
		test_func_s((const char *)ptr_char);
		test_func_s((const char *)"");
		test_func_s((const char *)NULL);
		free(ptr_char);
	}
	if ((argv[1][0] == 'p') || !ft_strncmp(argv[1] , "all", 3))
	{
		test_func_p(dummy_ptr1);
		test_func_p(dummy_ptr2);
		test_func_p(NULL);
	}
	if ((argv[1][0] == 'd') || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_d(tab[i]);
	if ((argv[1][0] == 'i') || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_i(tab[i]);
	if ((argv[1][0] == 'u') || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_u((unsigned int)tab[i]);
	if ((argv[1][0] == 'x') || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_x((unsigned int)tab[i]);
	if ((argv[1][0] == 'X') || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_X((unsigned int)tab[i]);
	if ((argv[1][0] == '%') || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_percent();
#ifndef NONE
#ifdef SPECIFIER_F
	if (!ft_strncmp(argv[1], "f", 3) || !ft_strncmp(argv[1] , "all", 3))
	{
		printf("hey!!\n");
		while (++i < 7)
			test_func_f((double)i/1.777);
	}
#endif

#ifdef SPECIFIER_G
	if (!ft_strncmp(argv[1], "g", 3) || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_g((double)i/1.6663);
#endif

#ifdef SPECIFIER_E
	if (!ft_strncmp(argv[1], "n", 3) || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_e((double)i/3.333);
#endif

#ifdef SPECIFIER_N
	if (argv[1][0] == 'n' || !ft_strncmp(argv[1] , "all", 3))
		test_func_n(i);
#endif

#ifdef SPECIFIER_HI
	if (!ft_strncmp(argv[1], "hi", 3) || !ft_strncmp(argv[1] , "all", 3))
	{
		printf("hey!! in f\n");
		while (++i < 7)
			test_func_hi((short int)tab[i]);
	}
#endif

#ifdef SPECIFIER_HU
	if (!ft_strncmp(argv[1], "hu", 3) || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_hu((short int)tab[i]);
#endif

#ifdef SPECIFIER_HX
	if (!ft_strncmp(argv[1], "hx", 3) || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_hx((short int)tab[i]);
#endif

#ifdef SPECIFIER_HHI
	if (!ft_strncmp(argv[1], "hhi", 3) || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_hhi((signed char)tab[i]);
#endif

#ifdef SPECIFIER_HHU
	if (!ft_strncmp(argv[1], "hhu", 3) || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_hhu((signed char)tab[i]);
#endif

#ifdef SPECIFIER_HHX
	if (!ft_strncmp(argv[1], "hhx", 3) || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_hhx((signed char)tab[i]);
#endif

#ifdef SPECIFIER_LI
	if (!ft_strncmp(argv[1], "li", 3) || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_li((long int)tab[i]);
#endif

#ifdef SPECIFIER_LU
	if (!ft_strncmp(argv[1], "lu", 3) || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_lu((long int)tab[i]);
#endif

#ifdef SPECIFIER_LX
	if (!ft_strncmp(argv[1], "lx", 3) || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_lx((long int)tab[i]);
#endif

#ifdef SPECIFIER_LLI
	if (!ft_strncmp(argv[1], "lli", 3) || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_lli((long long int)tab[i]);
#endif

#ifdef SPECIFIER_LLU
	if (!ft_strncmp(argv[1], "llu", 3) || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_llu((long long int)tab[i]);
#endif

#ifdef SPECIFIER_LLX
	if (!ft_strncmp(argv[1], "llx", 3) || !ft_strncmp(argv[1] , "all", 3))
		while (++i < 7)
			test_func_llx((long long int)tab[i]);
#endif
#endif
	return (0);
}
