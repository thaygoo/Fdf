/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:57:39 by hburton           #+#    #+#             */
/*   Updated: 2025/01/21 15:31:53 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen_GNL(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_is_new_line_GNL(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_set_stack_GNL(char **s)
{
	free(*s);
	*s = NULL;
	return (NULL);
}

char	*ft_join_GNL(char *stack, char **ret, char *buff)
{
	*ret = stack;
	stack = ft_strjoin_GNL(*ret, buff);
	return (stack);
}

char	*ft_strjoin_GNL(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	len1;
	size_t	len2;

	i = -1;
	j = -1;
	len1 = ft_strlen_GNL(s1);
	len2 = ft_strlen_GNL(s2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (++i < len1)
		str[i] = s1[i];
	while (++j < len2)
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}
