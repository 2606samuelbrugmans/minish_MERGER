/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_bzero.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/16 18:29:55 by stephen		   #+#	#+#			 */
/*   Updated: 2024/09/16 19:24:06 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_bzero(void *targ, size_t n)

{
	char	*str;

	str = targ;
	while (n > 0)
	{
		*str = 0;
		str ++;
		n --;
	}
	return (targ);
}

/*int	main(void)
{
	char	str[] = "Bonjour";
	printf("%s", (char *) ft_bzero(str, 3));
	return (0);
}*/
