/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putnbr_fd.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/30 18:23:20 by scesar			#+#	#+#			 */
/*   Updated: 2024/05/02 10:52:17 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else
	{
		if (nb < 0)
		{
			write(fd, "-", 1);
			nb *= -1;
		}
		if (nb <= 9)
		{
			ft_putchar_fd(nb + 48, fd);
		}
		else
		{
			ft_putnbr_fd(nb / 10, fd);
			ft_putnbr_fd(nb % 10, fd);
		}
	}
}

/*int	main(void)
{
	int	i = -57;
	int	fd = 2;

	ft_putnbr_fd(i, fd);
	return(0);
}*/
