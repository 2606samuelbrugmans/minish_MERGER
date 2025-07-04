/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memset.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/12 14:41:14 by scesar			#+#	#+#			 */
/*   Updated: 2024/09/16 19:23:14 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memset(void *targ, int c, size_t len)
{
	size_t			i;
	unsigned char	*set_targ;

	i = 0;
	set_targ = (unsigned char *) targ;
	while (len > 0)
	{
		*(unsigned char *)(set_targ + i) = (unsigned char) c;
		i ++;
		len --;
	}
	return (targ);
}

/*int	main(void)
{
	char	str[] = "Bonjour";
	char	str2[] = "Bonjour";
	printf("%s\n", (char *) ft_memset(str, 'A', 8));
	printf("%s\n", (char *) memset(str2, 'A', 8));
	return (0);
}*/
