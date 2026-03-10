/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer_PTF.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:42:47 by huburton          #+#    #+#             */
/*   Updated: 2025/01/21 15:41:42 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putpointer_PTF(unsigned long int ptr, int i)
{
	int	len;

	len = 0;
	if (ptr == 0)
	{
		ft_putstring_PTF("(nil)");
		return (5);
	}
	if (i == 1)
	{
		if (ft_putstring_PTF("0x") < 0)
			return (-1);
		len += 2;
	}
	if (ptr >= 16)
		len += ft_putpointer_PTF(ptr / 16, 0);
	if (ft_putchar_PTF("0123456789abcdef"[ptr % 16]) < 0)
		return (-1);
	return (len + 1);
}
