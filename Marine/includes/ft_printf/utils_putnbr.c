/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_putnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:11:57 by marthoma          #+#    #+#             */
/*   Updated: 2025/12/01 14:52:36 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_pf(int n)
{
	int long	i;
	int			count_bytes;

	count_bytes = 0;
	if (n == -2147483648)
		return (if_putnbr_intmin());
	i = n;
	if (i < 0)
	{
		write(1, "-", 1);
		i = -i;
		count_bytes++;
	}
	if (i > 9)
	{
		count_bytes += ft_putnbr_pf(i / 10);
		ft_putchar_pf((i % 10) + '0');
		count_bytes++;
	}
	if (i < 10)
	{
		ft_putchar_pf(i + '0');
		count_bytes++;
	}
	return (count_bytes);
}

int	if_putnbr_intmin(void)
{
	write(1, "-2147483648", 11);
	return (11);
}

int	calcul_len(unsigned int n)
{
	long	nbr;
	int		v;

	v = 0;
	nbr = n;
	if (nbr < 0)
	{
		v++;
		nbr = -nbr;
	}
	while (nbr >= 10)
	{
		nbr = nbr / 10;
		v++;
	}
	return (v + 1);
}

int	ft_putnbr_u_pf(unsigned int n, int count_bytes)
{
	unsigned long	i;
	char			zero;

	zero = '0';
	i = n;
	count_bytes = calcul_len(n);
	if (i == 0)
	{
		write(1, &zero, 1);
		return (1);
	}
	if (i > 9)
	{
		ft_putnbr_u_pf((i / 10), count_bytes);
		ft_putchar_pf((i % 10) + '0');
	}
	if (i < 10)
		ft_putchar_pf(i + '0');
	return (count_bytes);
}
