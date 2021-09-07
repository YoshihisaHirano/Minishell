#include "libft.h"

size_t	ft_strlen(char const *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		counter = counter + 1;
	}
	return (counter);
}
