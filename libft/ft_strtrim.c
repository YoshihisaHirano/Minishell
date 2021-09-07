#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*first;
	char	*last;
	size_t	length;
	char	*trimmed;

	if (!s1)
		return (NULL);
	length = ft_strlen(s1);
	first = (char *)s1;
	last = first + length;
	while (ft_strchr(set, *first) && first < last)
		first++;
	while (ft_strchr(set, *last) && last > first)
		last--;
	trimmed = ft_substr(first, 0, last - first + 1);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}
