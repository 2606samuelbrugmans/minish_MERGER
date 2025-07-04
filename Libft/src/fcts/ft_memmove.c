/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memmove.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/17 00:30:10 by stephen		   #+#	#+#			 */
/*   Updated: 2024/09/16 19:23:16 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*str_src;
	unsigned char		*str_dst;

	if (!dst && !src)
		return (NULL);
	str_src = (unsigned char *) src;
	str_dst = (unsigned char *) dst;
	if (str_dst < str_src)
	{
		while (len > 0)
		{
			*str_dst++ = *str_src++;
			len --;
		}
	}
	else
	{
		str_src += (len - 1);
		str_dst += (len - 1);
		while (len --)
			*str_dst-- = *str_src--;
	}
	return (dst);
}

/*int	main(void)
{
	char	str_s[] = "Bonjour";
	char	str_d[] = "Saljour";
	char	str_d2[] = "Saljour";
	printf("%s\n", (char *) ft_memmove(NULL, str_s, 3));
	printf("%s\n", (char *)memmove(NULL, str_s, 3));
	return (0);
}

int		main(int argc, const char *argv[])
{
	char	src[] = "lorem ipsum dolor sit amet";
	char	*dest;
	int		arg;

	dest = src + 1;
	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
	{
		if (dest != ft_memmove(dest, "consectetur", 5))
			write(1, "dest's adress was not returned\n", 31);
		write(1, dest, 22);
	}
	else if (arg == 2)
	{
		if (dest != ft_memmove(dest, "con\0sec\0\0te\0tur", 10))
			write(1, "dest's adress was not returned\n", 31);
		write(1, dest, 22);
	}
	else if (arg == 3)
	{
		if (dest != ft_memmove(dest, src, 8))
			write(1, "dest's adress was not returned\n", 31);
		write(1, dest, 22);
	}
	else if (arg == 4)
	{
		if (src != ft_memmove(src, dest, 8))
			write(1, "dest's adress was not returned\n", 31);
		write(1, dest, 22);
	}
	else if (arg == 5)
	{
		if (src != ft_memmove(src, dest, 0))
			write(1, "dest's adress was not returned\n", 31);
		write(1, dest, 22);
	}
	return (0);
}*/
