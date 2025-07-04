/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line_utils_bonus.c						:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/11 16:26:57 by scesar			#+#	#+#			 */
/*   Updated: 2024/07/02 17:58:45 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char	*str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len ++;
	return (len);
}

char	*ft_strdup(const char	*str)
{
	char	*cpy;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen((char *) str);
	cpy = (char *)malloc(len + 1);
	if (!cpy)
		return (NULL);
	while (str[i])
	{
		cpy[i] = str[i];
		i ++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len_s1;
	size_t	len_s2;
	size_t	len_tot;
	char	*fix;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len_tot = (len_s1 + len_s2);
	fix = (char *)malloc(sizeof(char) * (len_tot + 1));
	if (!fix)
		return (NULL);
	while (i < len_tot)
	{
		if (i < len_s1)
			fix[i] = *(s1 + i);
		if (i >= len_s1)
			fix[i] = *(s2 + i - len_s1);
		i++;
	}
	fix[i] = '\0';
	return (fix);
}

char	*ft_strrchr(const char *str, int c)
{
	char	*bingo;

	if (!str)
		return (NULL);
	bingo = NULL;
	while (*str)
	{
		if (*str == (char) c)
			bingo = (char *) str;
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (bingo);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = len;
	if (len > ft_strlen(s) - start)
		len_s = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	new_str = malloc(sizeof(char) * (len_s + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len && *(s + start) && start < ft_strlen(s))
	{
		new_str[i] = *(char *)(s + start);
		s++;
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
