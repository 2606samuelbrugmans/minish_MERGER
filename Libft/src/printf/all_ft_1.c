/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   all_ft_1.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/12 20:25:40 by stephen		   #+#	#+#			 */
/*   Updated: 2024/09/19 17:09:26 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_putnbr_fd_(int nb, int fd)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
		len += ft_putstr_fd_("-2147483648", 1);
	else
	{
		if (nb < 0)
		{
			len += ft_putchar_fd_('-', 1);
			nb *= -1;
		}
		if (nb <= 9)
			len += ft_putchar_fd_(nb + 48, fd);
		else
		{
			len += ft_putnbr_fd_(nb / 10, fd);
			len += ft_putnbr_fd_(nb % 10, fd);
		}
	}
	return (len);
}

int	ft_putnbr_unint_(unsigned int nb, int fd)
{
	int	len;

	len = 0;
	if (nb <= 9)
		len += ft_putchar_fd_(nb + 48, fd);
	else
	{
		len += ft_putnbr_unint_(nb / 10, fd);
		len += ft_putnbr_unint_(nb % 10, fd);
	}
	return (len);
}

int	ft_putchar_fd_(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstr_fd_(char *s, int fd)
{
	int	len;

	len = 0;
	if (!s)
	{
		ft_putstr_fd_("(null)", 1);
		return (6);
	}
	while (s[len])
		len += ft_putchar_fd_(s[len], fd);
	return (len);
}
