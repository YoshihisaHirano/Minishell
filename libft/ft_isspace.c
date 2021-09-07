int	ft_isspace(int c)
{
	if (c == '\r' || c == '\f' || c == '\t' || c == '\v'
		|| c == ' ' || c == '\n')
		return (1);
	return (0);
}
