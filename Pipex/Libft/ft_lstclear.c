/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcamara <gcamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:25:55 by gcamara           #+#    #+#             */
/*   Updated: 2026/01/31 17:34:10 by gcamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;

	current = NULL;
	while (*lst != NULL)
	{
		current = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = current;
	}
	free(*lst);
	*lst = NULL;
}
