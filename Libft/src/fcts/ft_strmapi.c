/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strmapi.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/01 21:04:25 by scesar			#+#	#+#			 */
/*   Updated: 2024/09/16 19:22:46 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

/*char  ft_toupperplus(unsigned int i, char c)
{
		i++;
		i--;
		if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*res;

	if (!s || !f)
		return (NULL);
	i = 0;
	res = ft_strdup(s);
	if (!res)
		return (NULL);
	while (res[i])
	{
		res[i] = (*f)(i, res[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*int main(void)
{
		char const s[15] = "Salut les amis";
		printf("%s", ft_strmapi(s, &ft_toupperplus));
		return (0);
}*/
