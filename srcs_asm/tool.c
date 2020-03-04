int		is_label_char(char c)
{
	char	tab[26];

	tab = "";
	while (tab != NULL)
	{
		if (c == *tab)
			return (TRUE);
		tab++;
	}
	return (FALSE);
}