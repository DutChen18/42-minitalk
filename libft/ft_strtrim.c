/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: csteenvo <csteenvo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 13:30:49 by csteenvo      #+#    #+#                 */
/*   Updated: 2022/01/18 13:30:49 by csteenvo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strtrim(const char *str1, const char *str2)
{
	const char	*str;
	size_t		max;

	if (FT_SAFE >= 1 && (str1 == NULL || str2 == NULL))
		return (NULL);
	while (*str1 && ft_strchr(str2, *str1))
		str1 += 1;
	str = str1;
	max = 0;
	while (*str1)
	{
		if (!ft_strchr(str2, *str1))
			max = str1 - str + 1;
		str1 += 1;
	}
	return (ft_substr(str, 0, max));
}
