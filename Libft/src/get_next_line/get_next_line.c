/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/02 14:50:41 by scesar			#+#	#+#			 */
/*   Updated: 2024/07/02 17:44:31 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_line(int fd, char *buff, char *save)
{
	int		byte_read;
	char	*temp;

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buff, BUFFER_SIZE);
		if (byte_read <= 0)
			break ;
		buff[byte_read] = '\0';
		if (!save)
			save = ft_strdup("");
		temp = save;
		save = ft_strjoin (temp, buff);
		free(temp);
		temp = NULL;
		if (!save)
			return (NULL);
		if (ft_strrchr(buff, '\n'))
			break ;
	}
	if (byte_read == -1)
		return (NULL);
	return (save);
}

char	*update_save(char *line)
{
	size_t	next_bsn;
	char	*up_save;

	next_bsn = 0;
	while (line[next_bsn] && line[next_bsn] != '\n')
		next_bsn ++;
	if (line[next_bsn] == '\0')
		return (NULL);
	up_save = ft_substr(line, next_bsn + 1, ft_strlen(line) - next_bsn);
	if (!up_save)
		return (NULL);
	if (*up_save == '\0')
	{
		free(up_save);
		up_save = NULL;
	}
	line[next_bsn + 1] = '\0';
	return (up_save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	char		*buff;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	line = fill_line (fd, buff, save);
	free(buff);
	buff = NULL;
	if (!line)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	save = update_save(line);
	return (line);
}

// int main(void)
// {
// 	char *str;
//	 int fd = open("test.txt", O_RDONLY);
//	 if (fd == -1)
//		 return(1);
// 	str = get_next_line(fd);
// 	while (str)
// 	{
// 		printf("line from main : %s \n", str);
// 		free(str);
// 		str = get_next_line(fd);
// 	}
// 	// free(str);
//	 close(fd);
//	 // system ("leaks a.out");
//	 return (0);
// }
