/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strlcpy.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/19 13:18:49 by scesar			#+#	#+#			 */
/*   Updated: 2024/09/16 19:22:52 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = (size_t) ft_strlen(src);
	if (dstsize == 0)
		return (res);
	while (i < res && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (res);
}

/*int	main(void)
{
	char	dst[15] = "";
	char	dst2[15] = "";
	char	*src = NULL;
	ft_strlcpy(dst, src, 0);
	printf("%s\n", dst);
	strlcpy(dst2, src, 0);
	printf("%s\n", dst2);
	return (0);
}*/
