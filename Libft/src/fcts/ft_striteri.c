/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_striteri.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/30 17:10:06 by scesar			#+#	#+#			 */
/*   Updated: 2024/09/16 19:22:58 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

/*void	ft_toupperplusplus(unsigned int i, char *str)
{
	while(str[i])
	{
		if (str[i] >= 97 && str[i] <= 122)
			str[i] -= 32;
		i++;
	}
}*/
// pas sur de comprendre diff avec strmapi
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*int main(void)
{
	char s[] = "Au revoir les amis";
	ft_striteri(s, &ft_toupperplusplus);
	printf("%s", s);
	return (0);
}*/
