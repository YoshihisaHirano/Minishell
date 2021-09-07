#include "libft.h"

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	b;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		a = (unsigned char)s1[i];
		b = (unsigned char)s2[i];
		if (a - b)
		{
			return (a - b);
		}
		i++;
	}
	return (0);
}
