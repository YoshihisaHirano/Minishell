#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*c_dst;
	const unsigned char	*c_src;

	c_dst = (unsigned char *)dst;
	c_src = (const unsigned char *)src;
	if (!src && !dst)
	{
		return (NULL);
	}
	while (n--)
		*c_dst++ = *c_src++;
	return (dst);
}
