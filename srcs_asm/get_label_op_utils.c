#include "../includes/asm.h"
#include "../libft/includes/libft.h"

static void			init_tab(char *tab[16])
{
	tab[0] = "live";
	tab[1] = "ld";
	tab[2] = "st";
	tab[3] = "add";
	tab[4] = "sub";
	tab[5] = "and";
	tab[6] = "or";
	tab[7] = "xor";
	tab[8] = "zjmp";
	tab[9] = "ldi";
	tab[10] = "sti";
	tab[11] = "fork";
	tab[12] = "lld";
	tab[13] = "lldi";
	tab[14] = "lfork";
	tab[15] = "aff";
}					

int8_t				found_op_code(char **line)
{
	char 	*tab[16];
	int		i;
	int		j;


	init_tab(tab);
	i = 0;
	j = 0;
	while ((*line)[j] != ' ' && (*line)[j] != '\t' && (*line)[j] != '\0')
		j++;
	while(i < 16)
	{
		if (ft_strncmp(*line, tab[i], j) == 0)
		{
			(*line) += j;
			return (i + 1);
		}
		i++;
	}
	return (0);
}

void    			update_oct(t_stack *stack, size_t op)
{    
	if (op != 1 && op != 9 && op != 12 && op != 15)
		stack->cur_label->encod_b = 1;
	stack->oct = stack->oct + stack->cur_label->encod_b + 1;
}


int					is_label_char(char c)
{
	char		*tab;

	tab = "abcdefghijklmnopqrstuvwxyz_0123456789";
	while (*tab)
	{
		if (c == *tab)
			return (1);
		tab++;
	}
	return (0);
}


void				label(t_stack *stack, char **line)
{
	t_list		*new;
	t_label		label;
	int			i;

	i = 0;
	ft_bzero(&label, sizeof(t_label));
	while (is_label_char((*line)[i]) == 1)
		i++;
	if ((*line)[i++] == ':')
	{
		label.name = ft_strndup(*line, --i);
		*line += (i + 1);
		if (label.name == NULL)
			stack->error = MALLOC_ERR;
	}
	label.oct = stack->oct;
	new = ft_lstnew(&label, sizeof(t_label));
	if (new == NULL || stack->error != NO_ERR)
	{
		stack->error = MALLOC_ERR;
		return ;
	}
	ft_lstadd_back(&(stack->label_list), new);
	stack->cur_label = (t_label*)new->content;
}

