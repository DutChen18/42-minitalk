#include "libft.h"
#include <stdlib.h>

char
	*ft_strjoin(const char *str1, const char *str2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	if (FT_SAFE >= 1 && (str1 == NULL || str2 == NULL))
		return (NULL);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	res = malloc(len1 + len2 + 1);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, str1, len1);
	ft_memcpy(res + len1, str2, len2);
	res[len1 + len2] = '\0';
	return (res);
}
