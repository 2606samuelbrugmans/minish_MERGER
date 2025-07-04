/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   all_ft_2.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/12 19:52:27 by stephen		   #+#	#+#			 */
/*   Updated: 2024/09/19 17:12:08 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/ft_printf.h"

int	ft_puthexa_min_fd_(unsigned long nb, int fd)
{
	int		len;
	char	*base;

	len = 0;
	base = "0123456789abcdef";
	if (nb < 16)
		len += ft_putchar_fd_(base[nb], fd);
	else
	{
		len += ft_puthexa_min_fd_((nb / 16), fd);
		len += ft_puthexa_min_fd_((nb % 16), fd);
	}
	return (len);
}

int	ft_puthexa_maj_fd_(unsigned long nb, int fd)
{
	int		len;
	char	*base;

	len = 0;
	base = "0123456789ABCDEF";
	if (nb < 16)
		len += ft_putchar_fd_(base[nb], fd);
	else
	{
		len += ft_puthexa_maj_fd_((nb / 16), fd);
		len += ft_puthexa_maj_fd_((nb % 16), fd);
	}
	return (len);
}

int	ft_putmem_ad_fd_(void *ptr, int fd)
{
	int				len;
	unsigned long	ptr_ad;

	len = 0;
	ptr_ad = (unsigned long) ptr;
	len += ft_putstr_fd_("0x", fd);
	len += ft_puthexa_min_fd_(ptr_ad, fd);
	return (len);
}
