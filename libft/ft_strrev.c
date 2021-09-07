char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	*start;
	char	temp;

	start = str;
	len = 0;
	i = 0;
	while (*str)
	{
		len++;
		str++;
	}
	str--;
	while (i < (len / 2))
	{
		temp = start[i];
		start[i] = (*str);
		start[len - 1 - i] = temp;
		i++;
		str--;
	}
	return (start);
}
