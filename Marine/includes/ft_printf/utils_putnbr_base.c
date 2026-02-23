/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_putnbr_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:07:38 by marthoma          #+#    #+#             */
/*   Updated: 2026/02/13 16:19:34 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft/libft.h"

int	ft_putnbr_base_p(unsigned long pointer, char *base)
{
	unsigned long	base_len;
	unsigned long	n;
	int				count_bytes;

	n = pointer;
	base_len = ft_strlen(base);
	count_bytes = 0;
	if (n >= base_len)
	{
		count_bytes += ft_putnbr_base_p((n / base_len), base);
		count_bytes += ft_putnbr_base_p((n % base_len), base);
	}
	if (n < base_len)
		count_bytes += ft_putchar_pf(base[n]);
	return (count_bytes);
}

int	ft_putnbr_base(int nbr, char *base)
{
	int			base_len;
	int long	n;
	int			count_bytes;

	count_bytes = 0;
	n = (long)nbr;
	base_len = ft_strlen(base);
	if (n < 0)
	{
		ft_putchar_pf('-');
		n = -n;
		count_bytes++;
	}
	if (n >= base_len)
	{
		count_bytes += ft_putnbr_base((n / base_len), base);
		count_bytes += ft_putnbr_base(n % base_len, base);
	}
	else
	{
		ft_putchar_pf(base[n]);
		count_bytes++;
	}
	return (count_bytes);
}

int	ft_putnbr_base_u(unsigned int nbr, char *base)
{
	unsigned long	base_len;
	unsigned long	n;
	int				count_bytes;

	count_bytes = 0;
	n = (unsigned long)nbr;
	base_len = ft_strlen(base);
	if (n < 0)
	{
		ft_putchar_pf('-');
		n = -n;
		count_bytes++;
	}
	if (n >= base_len)
	{
		count_bytes += ft_putnbr_base_u((n / base_len), base);
		count_bytes += ft_putnbr_base_u(n % base_len, base);
	}
	else
	{
		ft_putchar_pf(base[n]);
		count_bytes++;
	}
	return (count_bytes);
}
