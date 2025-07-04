/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strtrim.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/26 14:14:05 by scesar			#+#	#+#			 */
/*   Updated: 2024/09/16 19:22:25 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

int	check_if_in(char x, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == x || x == '\0')
			return (1);
		i ++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		finish;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && check_if_in(s1[start], set))
		start++;
	finish = ft_strlen(s1) - 1;
	while (finish > start && check_if_in(s1[finish], set))
		finish--;
	res = ft_substr(s1, start, (finish - start) + 1);
	return (res);
}

// pas sur de comprendre l'indice mais ça fonctionne
/*int	main(void)
{
	char	*s1 = "23Tout va123bien412";
	char	*s2 = "1234";
	printf("%s", ft_strtrim(s1, s2));
	return (0);
}*/
