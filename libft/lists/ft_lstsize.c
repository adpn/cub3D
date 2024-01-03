/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:46:41 by alexphil          #+#    #+#             */
/*   Updated: 2023/09/11 16:42:38 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Counts the number of elements in a list.
int	ft_lstsize(t_list *lst)
{
	if (!lst)
		return (0);
	return (ft_lstsize(lst->next) + 1);
}
