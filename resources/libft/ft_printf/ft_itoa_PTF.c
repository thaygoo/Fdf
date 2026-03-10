/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_PTF.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:00:09 by huburton          #+#    #+#             */
/*   Updated: 2025/01/21 15:43:16 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_count_PTF(long int num)
{
	long int	n;
	int			i;

	i = 0;
	n = num;
	while (n)
	{
		n /= 10;
		i++;
	}
	i += (num == 0 || num < 0);
	return (i);
}

char	*ft_itoa_PTF(long int number)
{
	int		len;
	char	*str;

	len = ft_count_PTF(number);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (number < 0)
	{
		str[0] = '-';
		number = -number;
	}
	str[len--] = '\0';
	while (number > 9)
	{
		str[len--] = (number % 10) + 48;
		number /= 10;
	}
	str[len] = (number % 10) + 48;
	return (str);
}
