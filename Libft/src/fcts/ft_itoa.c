/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_itoa.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/29 18:22:19 by scesar			#+#	#+#			 */
/*   Updated: 2024/09/16 19:23:22 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	len_int(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n *= -1;
		count ++;
	}
	while (n >= 10)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static int	expo(int x)
{
	int	res;

	res = 1;
	while (x > 0)
	{
		res *= 10;
		x--;
	}
	return (res);
}

static char	*if_neg(int n, int len, char *res)
{
	int	conv;
	int	i;

	i = 0;
	res[i] = '-';
	n *= -1;
	i++;
	len --;
	while (len > 0)
	{
		conv = ((n / expo(len - 1)) % 10);
		res[i] = conv + '0';
		i++;
		len --;
	}
	res[i] = '\0';
	return (res);
}

static char	*if_pos(int n, int len, char *res)
{
	int	conv;
	int	i;

	i = 0;
	while (len > 0)
	{
		conv = ((n / expo(len - 1)) % 10);
		res[i] = conv + '0';
		i++;
		len --;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = len_int(n);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	if (n < 0)
		res = if_neg(n, len, res);
	else
		res = if_pos(n, len, res);
	return (res);
}

/*int	main(void)
{
	int	x = (-2147483648);
	printf("%s\n", ft_itoa(x));
	return(0);
}*/
