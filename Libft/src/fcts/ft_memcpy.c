/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memcpy.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/16 19:00:20 by stephen		   #+#	#+#			 */
/*   Updated: 2024/09/16 19:23:17 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*str_src;
	char		*str_dst;

	if (!dst && !src)
		return (NULL);
	str_src = src;
	str_dst = dst;
	while (n > 0)
	{
		*str_dst = *str_src;
		str_src ++;
		str_dst ++;
		n --;
	}
	return (dst);
}

/*int	main(void)
{
	char	str_s[] = "Bonjour";
	char	str_d[] = "Saljour";
	char	str_d2[] = "Saljour";
	printf("%s\n", (char *) ft_memcpy(NULL, NULL, 3));
	printf("%s\n", (char *)memcpy(NULL, NULL, 3));
	return (0);
}*/
