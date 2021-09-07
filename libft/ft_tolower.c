int	ft_tolower(int c)
{
	if (!(c > 64 && c < 91))
		return (c);
	return (c + 32);
}
