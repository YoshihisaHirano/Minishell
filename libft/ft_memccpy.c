#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		u_c;
	const unsigned char	*c_src;
	unsigned char		*c_dst;	

	u_c = (unsigned char)c;
	c_src = (const unsigned char *)src;
	c_dst = (unsigned char *)dst;
	if (!src && !dst)
		return (NULL);
	while (n--)
	{
		*c_dst++ = *c_src;
		if (*c_src == u_c)
			return (c_dst);
		c_src++;
	}
	return (NULL);
}
