/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:45:05 by alexphil          #+#    #+#             */
/*   Updated: 2023/09/11 16:39:39 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Move byte string.
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;

	p_dst = dst;
	p_src = (unsigned char *) src;
	if (dst > src)
		while (len--)
			p_dst[len] = p_src[len];
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
