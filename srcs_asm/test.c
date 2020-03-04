

int8_t	found_op_code(char **line)
{
	char 	*tab[16];
	int		i;

	tab = {"live", "ld", "st", "add", "sub", "and", "or",
	"xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"};
	i = 0;
	while(i < 16)
	{
		if (ft_strncmp(*line, tab[i], ft_strlen(tab[i])) == 0)
		{
			*line += ft_strlen(tab[i]);
			return (i + 1);
		}
	}
	return (0);
}