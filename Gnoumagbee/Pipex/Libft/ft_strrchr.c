/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcamara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:28:16 by gcamara           #+#    #+#             */
/*   Updated: 2025/11/10 13:45:51 by gcamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		str_count;
	char	l;
	char	*str;

	l = (unsigned char)c;
	str = (char *)s;
	str_count = ft_strlen(str);
	i = 0;
	while (str_count >= 0)
	{
		if (str[str_count] == l)
		{
			return (&str[str_count]);
		}
		str_count--;
	}
	return (NULL);
}

/*int main ()
{
        char chaine[] = "coucou les licornes";
        printf("%s", ft_strrchr(chaine, 'c'));
        return(0);
}*/
