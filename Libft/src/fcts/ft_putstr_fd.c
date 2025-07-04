/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putstr_fd.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/30 18:12:38 by scesar			#+#	#+#			 */
/*   Updated: 2024/04/30 19:15:52 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

/*int main(void)
{
	char s[] = "Bonjour tout le monde";
	int	fd = 1;
	ft_putstr_fd(s, fd);
	return (0);
}*/
