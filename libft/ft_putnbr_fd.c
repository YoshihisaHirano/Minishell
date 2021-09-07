#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	char			result;
	unsigned int	u_nb;

	if (fd < 0)
		return ;
	if (nb < 0)
	{
		u_nb = nb * (-1);
		ft_putchar_fd('-', fd);
	}
	else
		u_nb = nb;
	if (u_nb < 10 && u_nb >= 0)
	{
		result = u_nb + '0';
		ft_putchar_fd(result, fd);
	}
	if (u_nb >= 10)
	{
		ft_putnbr_fd(u_nb / 10, fd);
		result = (u_nb % 10) + '0';
		ft_putchar_fd(result, fd);
	}
}
