/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:54:30 by alexphil          #+#    #+#             */
/*   Updated: 2023/09/11 16:39:29 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Copy memory area.
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;
	size_t			i;

	if (dst || src)
	{
		p_dst = dst;
		p_src = (unsigned char *) src;
		i = 0;
		while (n--)
		{
			p_dst[i] = p_src[i];
			i++;
		}
	}
	return (dst);
}
