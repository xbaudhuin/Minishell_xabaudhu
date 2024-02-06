/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xabaudhu <xabaudhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:11:44 by xabaudhu          #+#    #+#             */
/*   Updated: 2024/01/18 13:26:23 by xabaudhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

typedef struct s_flags
{
	int	zero;
	int	hash;
	int	minus;
	int	width;
	int	precision;
	int	space;
	int	plus;
	int	padding;
	int	fd;
}	t_flags;

int		ft_memcpy_size(void *dest, const void *src, int n);
int		ft_memmove_size(void *dest, const void *src, int n);
int		ft_memset_size(void *s, int c, int n);
int		ft_strlen_safe(const char *s);

int		print_format(const char *format, long int *to_print);
int		print_percent(int fd);
int		print_args(va_list args, const char *format, long int *to_print);
int		parse_format(const char *format, va_list args);
int		ft_printf(const char *format, ...);
void	init_flags(t_flags *flag);
int		is_end_flag(char c);
int		is_early_flags(const char c, t_flags *flag);
int		check_flag_error(t_flags *flag);
int		atoi_flag(const char *format, int *index);
int		parse_flags(t_flags *flag, const char *format);
int		check_type(va_list args, const char *format, t_flags *flag);

int		print_char(int c, t_flags *flag);

void	fill_string(char *str, char *ret, t_flags *flag);
int		print_string(char *str, t_flags *flag);

int		get_len_signed(int n);
int		get_signed_number(int n, int len, char *str);
int		fix_flag_signed(int n, t_flags *flag);
void	fill_signed(char *ret, t_flags *flag, int n, int len);
int		print_signed(int n, t_flags *flag);

int		get_len_unsigned(unsigned int nb, int radix);
int		fix_flag_unsigned(unsigned int nb, t_flags *flag, int size);

int		get_unsigned_number(unsigned int nb, int len, char *str);
void	fill_unsigned(char *ret, t_flags *flag, unsigned int nb, int len);
int		print_unsigned(unsigned int nb, t_flags *flag);

int		print_hexa(unsigned int nb, t_flags *flag, char *base);
char	*fill_hexa(char *base, t_flags *flag, unsigned int nb, int len);
int		hexa_to_str(unsigned int nb, int len, char *str, char *base);

int		get_len_address(void *ptr);
int		address_to_str(void *ptr, char *str, int len);
void	fill_memory(char *ret, t_flags *flag, void *ptr, int len);
int		print_memory(void *ptr, t_flags *flag);

int		ft_fprintf(int fd, const char *format, ...);
int		fparse_format(int fd, const char *format, va_list args);
int		fprint_args(int fd, va_list args, const char *format, long int *to_pri);
int		fprint_format(int fd, const char *format, long int *to_print);

#endif
