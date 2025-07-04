/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_printf.h										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: scesar <scesar@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/12 19:53:49 by stephen		   #+#	#+#			 */
/*   Updated: 2024/09/19 17:08:57 by scesar		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_putchar_fd_(char c, int fd);
int	ft_putstr_fd_(char *s, int fd);

int	ft_putnbr_fd_(int nb, int fd);
int	ft_putnbr_unint_(unsigned int nb, int fd);
int	ft_puthexa_min_fd_(unsigned long nb, int fd);
int	ft_puthexa_maj_fd_(unsigned long nb, int fd);

int	ft_putmem_ad_fd_(void *ptr, int fd);

int	args_match_format(const char format, va_list args_to_print);
int	ft_printf(const char *args_format, ...);

#endif
