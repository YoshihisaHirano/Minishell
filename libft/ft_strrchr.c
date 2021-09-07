#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*chr;
	char	sym;

	sym = (char)c;
	len = ft_strlen(s);
	chr = (char *)s;
	while (len > 0)
	{
		if (sym == *(chr + len))
			return (chr + len);
		len--;
	}
	if (sym == *(chr + len))
		return (chr + len);
	return (NULL);
}
