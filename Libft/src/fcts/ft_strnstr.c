/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strnstr.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/22 22:06:08 by scesar			#+#	#+#			 */
/*   Updated: 2024/09/16 19:22:32 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*res;
	int		jump_back;

	res = (char *) haystack;
	if (*needle == '\0')
		return (res);
	while (*res && len > 0)
	{
		jump_back = 0;
		while (*res == *needle && *needle != '\0' && len > 0)
		{
			res ++;
			needle ++;
			jump_back++;
			len--;
		}
		if (*needle == '\0')
			return (res - jump_back);
		res -= jump_back;
		needle -= jump_back;
		len += jump_back;
		len--;
		res++;
	}
	return (NULL);
}

/*int	main(void)
{
	char	x[] = "La vie est belle";
	char	y[] = "est";

	printf("%s\n", ft_strnstr(x, y, 3));
	printf("%s\n", strnstr(x, y, 3));
	return (0);
}*/
