/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_printf.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/15 14:20:58 by scesar			#+#	#+#			 */
/*   Updated: 2024/09/19 17:10:11 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	args_match_format(const char format, va_list args_to_print)
{
	int	ret_value;

	ret_value = 1;
	if (format == 'c')
		ret_value += ft_putchar_fd_(va_arg(args_to_print, int), 1);
	else if (format == 's')
		ret_value += ft_putstr_fd_(va_arg(args_to_print, char *), 1);
	else if (format == 'p')
		ret_value += ft_putmem_ad_fd_(va_arg(args_to_print, void *), 1);
	else if (format == 'd' || format == 'i')
		ret_value += ft_putnbr_fd_(va_arg(args_to_print, int), 1);
	else if (format == 'u')
		ret_value += ft_putnbr_unint_(va_arg(args_to_print, unsigned long), 1);
	else if (format == 'x')
		ret_value += ft_puthexa_min_fd_(va_arg(args_to_print, unsigned int), 1);
	else if (format == 'X')
		ret_value += ft_puthexa_maj_fd_(va_arg(args_to_print, unsigned int), 1);
	else if (format == '%')
		ret_value += ft_putchar_fd_('%', 1);
	else
		return (0);
	return (ret_value);
}

int	ft_printf(const char *args_format, ...)
{
	va_list	args_to_print;
	int		ret_value;
	int		check;

	va_start(args_to_print, args_format);
	ret_value = 0;
	while (*args_format)
	{
		check = 0;
		if (*args_format == '%')
		{
			args_format ++;
			check = args_match_format(*args_format, args_to_print);
			if (!check)
				return (ret_value);
			ret_value += (check - 1);
		}
		else
			ret_value += ft_putchar_fd_(*args_format, 1);
		args_format ++;
	}
	va_end(args_to_print);
	return (ret_value);
}

/*#include <stdio.h>
#include <limits.h>
int	main(void)
{
	// int a = -2147483648;
	int b = -469953;
	// char *x = NULL;
	// char y[] = "Salut !! \nÇa va ?";
	// char	z = '\n';
	// char	test_pc = '%';

	int my_res = ft_printf("%u", b);
	printf(" : ma ft_printf");
	printf("\n");
	printf("%i",my_res);
	printf(" : mon retrun");
	printf("\n");
	int true_res = printf("%u", b);
	printf(" : la vraie printf");
	printf("\n");
	printf("%i",true_res);
	printf(" : le vrai return");
	return(0);
}*/
