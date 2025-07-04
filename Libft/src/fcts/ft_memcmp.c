/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memcmp.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/22 14:35:15 by stephen		   #+#	#+#			 */
/*   Updated: 2024/09/16 19:23:20 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((n > 1) && (*str1 == *str2))
	{
		str1++;
		str2++;
		n --;
	}
	return (*str1 - *str2);
}
/*int	main(void)
{
	char	s1[] = "Salut mes amis !";
	char	s2[] = "Salut mes amis !";
	printf("%i\n", ft_memcmp(s1, s2, 17));
	printf("%i\n", memcmp(s1, s2, 17));
	return (0);
}*/
