/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_split.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/29 14:56:08 by stephen		   #+#	#+#			 */
/*   Updated: 2024/09/16 19:23:02 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

static char	*free_tab(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}
// suffisant comme sécu ?

static int	nbr_elem(char *str, char c)
{
	int	i;
	int	count;
	int	in_sep;

	i = 0;
	count = 0;
	in_sep = 0;
	while (str[i])
	{
		if (str[i] != c && !in_sep)
		{
			count ++;
			in_sep = 1;
		}
		else if (str[i] == c)
			in_sep = 0;
		i ++;
	}
	return (count);
}

static char	*new_elem(char *str, char c)
{
	char	*elem;
	int		i;
	int		len_elem;

	i = 0;
	len_elem = 0;
	while (str[len_elem] && str[len_elem] != c)
		len_elem++;
	elem = malloc(sizeof(char) * len_elem + 1);
	if (!elem)
		return (NULL);
	while (*str != c && *str != '\0')
	{
		elem[i] = *str;
		str ++;
		i ++;
	}
	elem[i] = '\0';
	return (elem);
}
// fonctionne avec return(ft_strtrim(elem,"")) pour optimiser memoire utilisée

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	res = (char **) malloc(sizeof(char *) * (nbr_elem((char *)s, c) + 1));
	if (!res)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != '\0')
		{
			res[i] = new_elem(((char *)s), c);
			if (res[i] == NULL)
				return (free_tab(res, i), NULL);
			i++;
		}
		while (*s != c && *s != '\0')
			s++;
	}
	res[i] = NULL;
	return (res);
}
/*int main(void)
{
	char const *str = "Salut  les copains  !!  ";
	char c = ' ';
	char	**tab = ft_split(str, c);
	int i = 0;
	while (tab[i] != NULL)
	{
		printf("%s\n", tab[i]);
		i++;
	}
	printf("%s\n", tab[i]);
	return (0);
}*/
