/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strrchr.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/19 16:38:20 by scesar			#+#	#+#			 */
/*   Updated: 2024/09/16 19:22:29 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		found;
	char	*res;

	found = 0;
	while (*s)
	{
		if (*s == (char) c)
		{
			res = (char *)s;
			found = 1;
		}
		s++;
	}
	if ((char) c == '\0')
		return ((char *)s);
	if (found)
		return (res);
	return (NULL);
}

/*int	main(void)
{
	char text[] = "MAIS IL EST OU ??";
	int c = 'M';
	printf("%s\n", ft_strrchr(text, c));
	printf("%s\n", strrchr(text, c));
	return (0);
}*/
