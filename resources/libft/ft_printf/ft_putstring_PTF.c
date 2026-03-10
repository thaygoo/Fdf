/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstring_PTF.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:42:43 by huburton          #+#    #+#             */
/*   Updated: 2025/01/21 15:41:31 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstring_PTF(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (ft_putstring_PTF("(null)"));
	while (str[len])
	{
		if (ft_putchar_PTF(str[len]) < 0)
			return (-1);
		len++;
	}
	return (len);
}
