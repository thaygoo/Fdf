/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_PTF.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:52:21 by huburton          #+#    #+#             */
/*   Updated: 2025/01/21 15:41:50 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_PTF(long int nbr)
{
	char	*str;
	int		rtn;

	str = ft_itoa_PTF(nbr);
	if (!str)
		return (-1);
	rtn = ft_putstring_PTF(str);
	free(str);
	return (rtn);
}
