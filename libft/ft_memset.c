
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*x;

	x = b;
	i = 0;
	while (i < len)
	{
		x[i] = c;
		i++;
	}
	return (b);
}
