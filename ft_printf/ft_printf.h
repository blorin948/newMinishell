/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 23:47:40 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 18:49:39 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_va_list_wrap
{
	va_list arg;
}				t_va_list_wrap;
int				ft_printf(const char *s, ...)
 __attribute__((format(printf,1,2)));
int				ft_atoi1(char *str, int i);
int				convert_type_adress(char *s, va_list argue, int par);
int				add_space_before(char *str, int len, int *param, int i);
int				add_space_after(char *str, int len, int *param, int i);
int				write_zero(char *str, int len, int *param, int i);
int				is_zero(char *str, int i);
char			convert_hexa_p(unsigned long i);
int				hexa_len_hexa(unsigned int n);
char			*ft_strrev(char *str);
int				write_between(char *str, int i, int *c);
int				is_space_after(char *str, int i);
int				write_end(char *str, int par);
int				parse_str(char *str);
int				ft_intlen(long n);
int				add_precision_int(int len, int param);
char			*convert_p(unsigned long n);
int				write_p(int n);
int				convert_x_p(unsigned long n, int *c, unsigned long a);
int				is_string(char *str, int i);
int				is_precision(char *str, int i);
int				convert_type_int(char *s, va_list argue, int par);
int				ft_putstr1(char *str);
char			convert_hexa(unsigned int i);
int				add_space_before_pourcent(char *str, int i, int *param);
int				ft_strlen1(char *str);
int				*assign_tab(int *tab);
int				add_negative(int *param, int len, int *c);
int				write_space_pourcent(char *str, int i, int *param);
void			ft_putnbr(long n, int *c);
int				write_zero_pourcent(char *str, int i, int *param);
int				convert_type_hexa(char *s, va_list argue, int par);
int				convert_x(unsigned int n, int *c, unsigned int a);
void			ft_putnbr_unsigned(unsigned int n, int *c);
int				add_precision(int len, int param);
int				write_space(char *str, int len, int *param, int i);
char			*is_str_valid(char *str);
int				count_precision(char *str, int len, int param, int i);
int				is_space(char *str, int i);
int				ft_unsigned_len(unsigned long n);
int				count_precision_string(char *str, int len, int param, int i);
void			ft_putchar(char c);
int				is_valid_after(char *str, int i, int param);
int				convert_type_pourcent(char *s, va_list argue, int par);
int				write_string(char *str, int len);
int				is_valid_before(char *str, int i, int param);
int				hexa_len(unsigned long n);
void			ft_free1(char *str);
int				use_argue(char *s, va_list argue);
int				is_pourcent(char *s);
int				convert_type_hexa_m(char *s, va_list argue, int par);
int				convert_type_unsigned(char *s, va_list argue, int par);
int				convert_type_char(char *s, va_list argue, int par);
int				convert_type_string(char *s, va_list argue, int par);
char			what_type(char *str, int i);
#endif
