/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strjoin.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/26 12:43:43 by scesar			#+#	#+#			 */
/*   Updated: 2024/09/16 19:22:56 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

static char	*ft_jumpback(char *str, int total_len)
{
	str -= (total_len);
	return (str);
}
// dif entre char const et const char ?

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (*s1)
	{
		*res = *s1;
		res++;
		s1++;
	}
	while (*s2)
	{
		*res = *s2;
		res++;
		s2++;
	}
	*res = '\0';
	res = ft_jumpback(res, len);
	return (res);
}

/*int	main(void)
{
	printf("%s", ft_strjoin("La vie ","est belle"));
	return (0);
}*/
