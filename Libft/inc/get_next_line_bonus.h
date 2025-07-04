/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line_bonus.h							  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/11 16:21:33 by scesar			#+#	#+#			 */
/*   Updated: 2024/10/25 16:44:34 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# define MAX_FD 1024
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024

# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

size_t	ft_strlen(const char	*str);
char	*ft_strdup(const char	*str);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strrchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*get_next_line(int fd);

#endif
