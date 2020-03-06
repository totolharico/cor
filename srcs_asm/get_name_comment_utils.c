#include "../includes/asm.h"
#include "../libft/includes/libft.h"

int				count_name_comment(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n' && str[i] != '#' && str[i] != ';')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i--;
	return (i);
}