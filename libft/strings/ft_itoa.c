/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:49:36 by alexphil          #+#    #+#             */
/*   Updated: 2023/09/11 16:31:11 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Return the length of an integer.
static size_t	nb_len(int n)
{
	int	len;

	len = (n == 0);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

// Transform an integer into a string.
char	*ft_itoa(int n)
{
	ssize_t	nb;
	size_t	neg;
	size_t	len;
	char	*res;

	nb = n;
	neg = (nb < 0);
	if (neg)
		nb = -nb;
	len = nb_len(nb);
	res = malloc((neg + len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '-';
	res[neg + len] = '\0';
	while (len > 0)
	{
		res[neg + len - 1] = nb % 10 + '0';
		nb /= 10;
		len--;
	}
	return (res);
}
