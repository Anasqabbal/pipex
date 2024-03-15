/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:49:22 by anqabbal          #+#    #+#             */
/*   Updated: 2023/12/05 09:56:15 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1)
	{
		if (*((unsigned char *)s1 + i) != *((unsigned char *)s2 + i))
			return ((*((unsigned char *)s1 + i)
					- *((unsigned char *)s2 + i)));
		i++;
	}
	return ((*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i)));
}
