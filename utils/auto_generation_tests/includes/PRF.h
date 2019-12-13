/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 00:56:13 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/08 23:18:20 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRF_H
# define PRF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define ASSERT_TEST 0
# define NORMAL_TEST 1

# define BASIC_FLA "-0.*"
# define BASIC_SPE "cspdiuxX%"
# define FILE_MK "../generated_tests/specifiers_and_srcs.mk"

# define GREEN "\033[38;5;2m"
# define RED "\033[38;5;1m"
# define CLEAR "\033[0m"
# define RANGE 4  //used for buiding the conversion_specifications file

# define F_MINU 0x20
# define F_ZERO 0x10
# define F_APPO 0x08
# define F_SPAC 0x04
# define F_HASH 0x02
# define F_PLUS 0x01

# define WARN_1 F_SPAC | F_PLUS
# define WARN_2 F_ZERO | F_MINU

# define STANDARD_MASK "__-0' #+"

void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_stringify(char *line);
void	ft_putnbr_fd(int n, int fd);
int		ft_toupper(int c);
char	*ft_strrchr(const char *s, int c);

char	*build_tmp_files(char *flags, char *std_mask, char *specifier, \
		int range);
int		update_mk_file(int fd_mk, char *specifier, char *name);
char	*modify_specifier_for_mk_file(char *specifier);

void	ask_for_the_matter(char *matter, char *subject_basic, \
		char *subject_bonus, int option);
char	*parse_user_input_matter(char *matter, char *subject_basic, \
		char *subject_bonus, int option);
int		parse_for_mistakes(char *user_input, char *subject_basic, \
		char *subject_bonus);
int		parse_extra_flags(char *line, char *subject_bonus);
void	ask_confirmation(char *matter, char *line);

char	**finish_parsing(char *basic_flags, char *basic_specifiers);
void	*free_double_dim_array(char **tab, int i);
int		ft_strlen_2d_array(char **array);
char	**split_specifiers(char *specifiers);
char	**get_user_choices(char *basic_flags, char *basic_specifiers);
char	**aggregate_bonus_and_subject(char *basic_flag, char *basic_specifier);
char	**build_combinaitions_from_extra_flags(char *extra_bonus);
char	*make_splitable(char *str, char c);
char	**ft_join_splits(char **tab1, char **tab2);
char	**prepend_chartab(char *str, char **tab);

char	*flags_build_combinations(char *usr_flags, char *std_mask, \
		char *specifier);
char	*create_name(char *base_name, char *specifier);
unsigned char  standardise_mask_flags(char *flags, const char *standard_mask);
unsigned char addapt_mask_specifier(unsigned char mask, char *spec);
char	*reduce_flags_to_str(unsigned char mask, char *std_flags);
int		write_flags_combos(char *flags, int fd);
int		parse_flags_comb_for_warnings(char *line);

char	*conversion_spec_build_comb(char *specifier, int range);
int		make_precision(char *padding, char *specifier, int fd_w, int range);
int		make_precision2(char *str, int fd_w, int range);
int		make_padding(char *specifier, int fd_w, int range);

char	*merge_flags_conv(char *flags, char* std_mask,char *specifier, \
		int range);
char	*merge_flags_conv_assist(char *file1, char *file2, char *specifier);
int		merge_for_real_the_f_files(int fd1, int fd_w, char *file2_name, \
		char *specifier);
int		check_for_warning_introductions(char *new, char *specifier);

char	*build_printf_file(char* file_read, char *specifier, int range);
int		build_printf_line(int fd_r, int fd_w, char *specifier, int range);
int		finish_build_printf_line(char *line, char *specifier, int fd_w, \
		int range, int start);
char	*start_build_printf_line(char *line, char *specifier);
void	append_end_to_call(char *line, char *specifier, int fd_w);
char	*substitute_star(char *line, int num);
char	*manage_the_n_case(char *line, char *specifier);

int		build_function_files(char *file_r, char *specifier, int option);
int		get_line_build_func_file(int fd_r, int fd_w, char *specifier, \
		int option);
int		initiate_beggining_func_file(int fd_w, char *specifier, int option);
char	*get_prototype_end(char *specifier);
char	*get_type(char *specifier);
int		writing_test_call(int fd_w, char *line, char *specifier, int *count);
int		writing_assert_call(int fd_w, char *line, int *count);
void	modify_for_debug(char **str);
char	*creat_name_for_c_file(char *tmp_name, int option);

int		success(char *str);
int		success_endl(char *str);
void	print_separator(void);
int		failure(char *str);
void	introduce_test(char *name);

#endif
