/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strchr.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/19 16:14:08 by scesar			#+#	#+#			 */
/*   Updated: 2024/09/16 19:23:01 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	if ((char) c == '\0')
		return ((char *) s);
	return (NULL);
}

/*void	ft_print_result(char const *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

int		main(int argc, const char *argv[])
{
	char		*str;
	char		str2[] = "bonjour";
	int			arg;

	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
	{
		if (!(str = ft_strchr(str2, 'b')))
			ft_print_result("NULL");
		else
		{
			ft_print_result(str);
			if (str != str2)
				ft_print_result("\nReturn value is false");
		}
	}
	else if (arg == 2)
	{
		if (!(str = ft_strchr(str2, 'o')))
			ft_print_result("NULL");
		else
		{
			ft_print_result(str);
			if (str != str2 + 1)
				ft_print_result("\nReturn value is false");
		}
	}
	else if (arg == 3)
	{
		if (!(str = ft_strchr(str2, 'j')))
			ft_print_result("NULL");
		else
		{
			ft_print_result(str);
			if (str != str2 + 3)
				ft_print_result("\nReturn value is false");
		}
	}
	else if (arg == 4)
	{
		if (!(str = ft_strchr(str2, 's')))
			ft_print_result("NULL");
		else
			ft_print_result(str);
	}
	else if (arg == 5)
	{
		if (!(str = ft_strchr(str2, '\0')))
			ft_print_result("NULL");
		else
		{
			ft_print_result(str);
			if (str != str2 + 7)
				ft_print_result("\nReturn value is false");
		}
	}
	else if (arg == 6)
	{
		char	str3[] = "";
		if (!(str = ft_strchr(str3, '\0')))
			ft_print_result("NULL");
		else
		{
			ft_print_result(str);
			if (str != str3)
				ft_print_result("\nReturn value is false");
		}
	}
	return (0);
}
int	main(void)
{
	char text[] = "La vie est belle";
	int c = 'e';

	if (ft_strchr(text, c) == strchr(text, c))
		printf("%s\n", "ok");
	printf("%s\n", ft_strchr(text, c));
	printf("%s\n", strchr(text, c));
	return (0);
}*/
