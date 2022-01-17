#include "libft.h"

char
	*ft_itoa(int num)
{
	char	buf[256];
	size_t	i;
	int		j;

	i = 255;
	buf[255] = '\0';
	while (1)
	{
		j = num % 10;
		i -= 1;
		buf[i] = '0' + j * (1 - (j < 0) * 2);
		num /= 10;
		if (num == 0)
			break ;
	}
	if (j < 0)
	{
		i -= 1;
		buf[i] = '-';
	}
	return (ft_strdup(buf + i));
}
