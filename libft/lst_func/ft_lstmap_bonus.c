/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:39:26 by sabrugie          #+#    #+#             */
/*   Updated: 2019/10/19 10:59:57 by sabrugie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void*))
{
	t_list	*res;

	if (!lst || !f || !del)
		return (0);
	if (!(res = ft_lstnew(lst->content)))
		return (0);
	res->content = (*f)(res->content);
	if (!lst->next)
	{
		res->next = 0;
		return (res);
	}
	if (!(res->next = ft_lstmap(lst->next, f, del)))
	{
		ft_lstdelone(res, del);
		return (res);
	}
	return (res);
}
