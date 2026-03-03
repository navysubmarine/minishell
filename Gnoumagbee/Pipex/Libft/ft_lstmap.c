/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcamara <gcamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 17:39:36 by gcamara           #+#    #+#             */
/*   Updated: 2026/01/31 17:38:38 by gcamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;

	new = NULL;
	while (lst != NULL)
	{
		new = f(lst->content);
		if (new == NULL)
		{
			ft_lstclear(new, del);
			return (NULL);
		}
		lst = lst->next;
		new = ft_lstnew(new->content);
	}
	return (new);
}
