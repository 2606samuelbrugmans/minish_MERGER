/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strdup.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/25 12:47:34 by stephen		   #+#	#+#			 */
/*   Updated: 2024/09/16 19:23:00 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strdup(const char *src)
{
	char	*ptr;
	int		len;
	int		i;

	len = ft_strlen((char *) src) + 1;
	ptr = (char *)malloc(len);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = src[i];
	return (ptr);
}
// ça veut dire quoi "NULL is returned and errno is set to ENOMEM" ?

/*int	main(void)
{
	printf("%s", ft_strdup("La vie est belle"));
	return (0);
}*/
