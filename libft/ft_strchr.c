#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*chr;
	char	sym;

	sym = (char)c;
	chr = (char *)s;
	while (*chr)
	{
		if (*chr == sym)
			return (chr);
		chr++;
	}
	if (sym == '\0')
		return (chr);
	return (NULL);
}
