#include "libft.h"

void	ft_putstr_fd(char const *str, int fd)
{
	size_t	len;

	if (!str || fd < 0)
		return ;
	len = ft_strlen(str);
	write(fd, str, len);
}
