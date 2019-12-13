/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRF_libft_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:44:35 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/08 23:18:09 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PRF.h"
#include "../includes/get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len1;
	size_t	len2;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(ptr = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	while (i < len1)
	{
		*(ptr + i) = *(s1 + i);
		i++;
	}
	while (i < len1 + len2)
	{
		*(ptr + i) = *(s2 + i - len1);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}

static int	predict_size(int n)
{
	int size;

	size = 0;
	if (n < 0)
		size++;
	while (n < -9 || n > 9)
	{
		size++;
		n = n / 10;
	}
	return (++size);
}

char		*ft_itoa(int n)
{
	char	*ptr;
	int		size;

	size = predict_size(n);
	if (!(ptr = (char *)malloc(sizeof(*ptr) * (size + 1))))
		return (NULL);
	ptr[size] = '\0';
	while ((n > 9) || (n < -9))
	{
		ptr[--size] = (n < 0) ? -(n % 10) + '0' : n % 10 + '0';
		n = n / 10;
	}
	ptr[--size] = (n < 0) ? -(n % 10) + '0' : n % 10 + '0';
	ptr[0] = (size == 1) ? '-' : ptr[0];
	return (ptr);
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	src_length;
	size_t	size_malloc;

	if (!s)
		return (NULL);
	src_length = ft_strlen(s);
	i = 0;
	if (start >= src_length)
		size_malloc = 1;
	else if (src_length - start < len)
		size_malloc = src_length - start + 1;
	else
		size_malloc = len + 1;
	if (!(str = (char *)malloc(sizeof(char) * size_malloc)))
		return (NULL);
	while (i < size_malloc - 1)
	{
		*(str + i) = *(s + start + i);
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	else
		return (NULL);
}
static int	find_start(char const *s, char c, int next_start)
{
	while (s[next_start] && s[next_start] == c)
		next_start++;
	return (next_start);
}

static int	find_end(char const *s, char c, int next_end)
{
	while (s[next_end] && s[next_end] == c)
		next_end++;
	while (s[next_end] && s[next_end] != c)
		next_end++;
	return (next_end);
}

static int	size_array(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static void	*free_nested(char **ptr, int k)
{
	while (--k >= 0)
	{
		free(ptr[k]);
		ptr[k] = NULL;
	}
	free(ptr);
	ptr = NULL;
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;
	int		k;
	int		j;

	i = 0;
	k = 0;
	if (!s || !(ptr = (char **)malloc(sizeof(char*) * (size_array(s, c) + 1))))
		return (NULL);
	ptr[size_array(s, c)] = NULL;
	while (k < size_array(s, c))
	{
		i = find_start(s, c, i);
		if (!(ptr[k] = (char *)malloc(sizeof(char) * (find_end(s, c, i) - i \
							+ 1))))
			return (free_nested(ptr, k));
		j = 0;
		while (s[i] && s[i] != c)
			ptr[k][j++] = s[i++];
		ptr[k][j] = '\0';
		k++;
	}
	return (ptr);
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

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (!needle[0])
	{
		return ((char *)haystack);
	}
	while (haystack[i] && (i < len))
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while ((i + j < len) && haystack[i + j] && needle[j] \
					&& *(haystack + i + j) == *(needle + j))
				j++;
			if (*(needle + j) == '\0')
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
static int	count_escape_sequence(char *str)
{
	int extra_len;
	int len;

	extra_len = 0;
	len = 0;
	if (!str)
		return (-1);
	while (str[len])
	{
		if (str[len] == '\n' || str[len] == '\t' || str[len] == '\\' \
			|| str[len] == '\r' || str[len] == '\b' || str[len] == '\"')
			extra_len++;
		len++;
	}
	return (extra_len + len);
}

char		*ft_stringify(char *line)
{
	char	*new;
	int		lim;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!line)
		return (NULL);
	lim = count_escape_sequence(line);
	if (!(new = (char*)malloc(sizeof(char) * (lim + 1))))
		return (NULL);
	new[lim] = '\0';
	while (++i < lim)
	{
		if (line[++j] == '\n' || line[j] == '\t' || line[j] == '\\' \
			|| line[j] == '\r' || line[j] == '\b' || line[j] == '\"')
		{
			new[i] = '\\';
			new[++i] = line[j];
		}
		else
			new[i] = line[j];
	}
	return (new);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n < -9)
			ft_putnbr_fd(-(n / 10), fd);
	}
	else if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	(n > 0) ? ft_putchar_fd(n % 10 + '0', fd) \
		: ft_putchar_fd(-(n % 10) + '0', fd);
}

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int position;

	position = -1;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == (char)c)
			position = i;
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	else if (position >= 0)
		return ((char *)(s + position));
	else
		return (NULL);
}
