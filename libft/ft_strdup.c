#include "libft.h"

char	*ft_strdup(char const *src)
{
	size_t		str_size;
	char		*cpy_ptr;
	size_t		i;

	i = 0;
	str_size = ft_strlen(src);
	cpy_ptr = malloc(str_size + 1);
	if (!cpy_ptr)
		return (NULL);
	while (i < str_size)
	{
		cpy_ptr[i] = src[i];
		i++;
	}
	cpy_ptr[i] = '\0';
	return (cpy_ptr);
}
