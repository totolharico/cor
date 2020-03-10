#include "../includes/asm.h"
#include "../libft/includes/libft.h"

int				count_name_comment(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '#' && str[i] != ';')
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	if (count % 2)
	{
		while (str[i] == ' ' || str[i] == '\t')
			i--;
		if (stack->dub == 1)
			
	}
}