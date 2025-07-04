/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memchr.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/22 12:55:56 by stephen		   #+#	#+#			 */
/*   Updated: 2024/09/16 19:23:21 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*res;

	res = (unsigned char *) s;
	while (n > 0)
	{
		if (*res == (unsigned char) c)
			return (res);
		res ++;
		n --;
	}
	return (NULL);
}

/*void	ft_print_result(const char *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

int		main(int argc, const char *argv[])
{
	const char *str;
	int			arg;

	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
	{
		str = ft_memchr("bonjour", 'b', 4);
		if (!str)
			ft_print_result("NULL");
		else
			ft_print_result(str);
	}
	else if (arg == 2)
	{
		str = ft_memchr("bonjour", 'o', 7);
		if (!str)
			ft_print_result("NULL");
		else
			ft_print_result(str);
	}
	else if (arg == 3)
	{
		str = ft_memchr("bonjourno", 'n', 2);
		if (!str)
			ft_print_result("NULL");
		else
			ft_print_result(str);
	}
	else if (arg == 4)
	{
		str = ft_memchr("bonjour", 'j', 6);
		if (!str)
			ft_print_result("NULL");
		else
			ft_print_result(str);
	}
	else if (arg == 5)
	{
		str = ft_memchr("bonjour", 's', 7);
		if (!str)
			ft_print_result("NULL");
		else
			ft_print_result(str);
	}
	else if (arg == 6)
	{
		int tab[7] = {-49, 49, 1, -1, 0, -2, 2};

		printf("%s", (char *)ft_memchr(tab, -1, 7));
	}
	   	return (0);
}
int	main(void)
{
	char	str[] = "Salut les amis !";
	char c = 'l';
	printf("%s\n", (char*) ft_memchr(str, c, 15));
	printf("%s\n", (char*) memchr(str, c, 15));
	return (0);
}*/
