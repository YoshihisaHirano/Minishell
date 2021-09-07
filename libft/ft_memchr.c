#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	u_c;
	unsigned char	*c_s;
	size_t			i;

	c_s = (unsigned char *)s;
	u_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (c_s[i] == u_c)
			return (c_s + i);
		i++;
	}
	return (NULL);
}
