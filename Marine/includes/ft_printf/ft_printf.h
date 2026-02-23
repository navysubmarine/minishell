/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:55:39 by marthoma          #+#    #+#             */
/*   Updated: 2026/02/13 15:48:57 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

void	ft_putstr_pf(char *s);
int		ft_strchr_pf(const char *s, int c);
int		ft_putchar_pf(char c);
int		ft_putnbr_pf(int n);
int		ft_printf(const char *s, ...);
int		ft_putnbr_u_pf(unsigned int u, int count_octets);
void	global_if(const char *s, va_list ap, int *ptr_i, int *ptr_count_bytes);
void	before_global_if(const char *s, va_list ap, int *ptr_i,
			int *ptr_count_bytes);
int		if_u_or_x_or_bigx(char c, unsigned int u, int count_bytes);
int		if_digit_or_int(int d, int count_bytes);
int		if_ptr(unsigned long ptr, int count_bytes);
int		if_str(char *str, int count_bytes);
int		if_char(int c);
int		calcul_len(unsigned int n);
int		ft_putnbr_base_p(unsigned long pointer, char *base);
int		if_putnbr_intmin(void);
int		ft_putnbr_base_u(unsigned int nbr, char *base);
int		ft_putnbr_base(int nbr, char *base);

#endif