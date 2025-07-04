/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_atoi.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/22 21:55:43 by scesar			#+#	#+#			 */
/*   Updated: 2024/09/16 19:24:08 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	res = 0;
	neg = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+' )
	{
		if (str[i] == '-')
			neg ++;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	if (neg == 1)
		return (res * -1);
	return (res);
}

/*int	main(void)
{
	printf("%d\n", ft_atoi(" 	-+1598461a6"));
	printf("%d\n", atoi(" 	-+1598461a6"));
	return (0);
}*/
