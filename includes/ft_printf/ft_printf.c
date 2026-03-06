/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marthoma <marthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:07:02 by marthoma          #+#    #+#             */
/*   Updated: 2025/12/04 11:33:38 by marthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	before_global_if(const char *s, va_list ap, int *ptr_i,
		int *ptr_count_bytes)
{
	if (s[*ptr_i] == '%')
	{
		global_if(s, ap, ptr_i, ptr_count_bytes);
		(*ptr_i)++;
	}
	else
		(*ptr_count_bytes) += if_char(s[*ptr_i]);
	(*ptr_i)++;
}

void	global_if(const char *s, va_list ap, int *ptr_i, int *ptr_count_bytes)
{
	if (s[*ptr_i + 1] == 'c')
		*ptr_count_bytes += if_char(va_arg(ap, int));
	else if (s[*ptr_i + 1] == 's')
		*ptr_count_bytes = if_str(va_arg(ap, char *), *ptr_count_bytes);
	else if (s[*ptr_i + 1] == 'p')
		*ptr_count_bytes = if_ptr((unsigned long)va_arg(ap, void *),
				*ptr_count_bytes);
	else if (s[*ptr_i + 1] == 'd' || s[*ptr_i + 1] == 'i')
		*ptr_count_bytes = if_digit_or_int(va_arg(ap, int), *ptr_count_bytes);
	else if (s[*ptr_i + 1] == 'u' || s[*ptr_i + 1] == 'x'
		|| s[*ptr_i + 1] == 'X')
		*ptr_count_bytes = if_u_or_x_or_bigx(s[*ptr_i + 1], va_arg(ap,
					unsigned int), *ptr_count_bytes);
	else if (s[*ptr_i + 1] == '%')
		*ptr_count_bytes += ft_putchar_pf('%');
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		count_bytes;
	int		*ptr_count_bytes;
	int		*ptr_i;
	int		i;

	va_start(ap, s);
	count_bytes = 0;
	i = 0;
	ptr_i = &i;
	ptr_count_bytes = &count_bytes;
	if (s == NULL)
		return (-1);
	while (s[*ptr_i])
	{
		before_global_if(s, ap, ptr_i, ptr_count_bytes);
	}
	va_end(ap);
	return (*ptr_count_bytes);
}

/*
int	main(void)
{
	char	*ptr;
	int		moi;
	int		og;

	moi = 0;
	og = 0;
	ptr = "crustace";
	// fflush(stdout);
	printf("ma version =\n");
	moi = ft_printf("iiii%c\n", 'c');
	printf("printf =\n");
	og = printf("iiii%c", 'c');
	printf("moi = %d\n", moi);
	printf("og = %d", og);
	return (0);
}
*/
