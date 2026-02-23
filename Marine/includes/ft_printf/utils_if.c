/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_if.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:40:01 by marthoma          #+#    #+#             */
/*   Updated: 2026/02/13 16:19:21 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft/libft.h"

int	if_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	if_str(char *str, int count_bytes)
{
	if (str == NULL)
	{
		write(1, "(null)", 6);
		count_bytes += 6;
		return (count_bytes);
	}
	ft_putstr_pf(str);
	return (count_bytes + ft_strlen(str));
}

int	if_ptr(unsigned long ptr, int count_bytes)
{
	char	zero;
	char	x;

	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		count_bytes += 5;
		return (count_bytes);
	}
	x = 'x';
	zero = '0';
	write(1, &zero, 1);
	write(1, &x, 1);
	count_bytes += 2;
	return (count_bytes + ft_putnbr_base_p(ptr, "0123456789abcdef"));
}

int	if_digit_or_int(int d, int count_bytes)
{
	return (count_bytes + ft_putnbr_pf(d));
}

int	if_u_or_x_or_bigx(char c, unsigned int u, int count_bytes)
{
	if (c == 'u')
		return (count_bytes + ft_putnbr_u_pf(u, count_bytes));
	else if (c == 'x')
		return (count_bytes + ft_putnbr_base_u(u, "0123456789abcdef"));
	else if (c == 'X')
		return (count_bytes + ft_putnbr_base_u(u, "0123456789ABCDEF"));
	else
		return (0);
}
