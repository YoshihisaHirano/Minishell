#include "libft.h"

void	ft_putendl_fd(char const *str, int fd)
{
	if (fd < 0)
		return ;
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
}
