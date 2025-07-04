/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_calloc.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/23 16:15:11 by scesar			#+#	#+#			 */
/*   Updated: 2024/09/16 19:24:02 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	total_size;

	total_size = count * size;
	if (size != 0 && total_size / size != count)
		return (NULL);
	res = malloc(total_size);
	if (!res)
		return (NULL);
	ft_bzero(res, total_size);
	return (res);
}

/*int main(void)
{
	int *ptr = ft_calloc(5, sizeof(int));
	int *ptr2 = calloc(5, sizeof(int));
	int	i = 0;

	if (ptr == NULL || ptr2 == NULL)
		return (0);
	while (i < 5)
	{
		printf("%d" , ptr[i]);
		i ++;
	}
	printf("\n");
	i = 0;
	while (i < 5)
	{
		printf("%d" , ptr2[i]);
		i ++;
	}
	free(ptr);
	free(ptr2);
	return (0);
}*/
