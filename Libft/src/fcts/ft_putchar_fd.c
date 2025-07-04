/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putchar_fd.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/30 18:07:30 by scesar			#+#	#+#			 */
/*   Updated: 2024/04/30 19:15:21 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*int main(void)
{
	char c = 'o';
	int	fd = 1;
	ft_putchar_fd(c, fd);
	return (0);
}*/
