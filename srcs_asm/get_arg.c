#include "../includes/asm.h"
#include "../libft/includes/libft.h"

 
static int		is_label_char(char c)
{
	char	*tab;

	tab = "abcdefghijklmnopqrstuvwxyz_0123456789";
	while (*tab)
	{
		if (c == *tab)
			return (1);
		tab++;
	}
	return (0);
}

void	parse_reg(t_stack *stack, char **line)
{
	(*line)++;
	if (**line < '0' && **line > '5')
	{
		stack->error = ARG_ERR;
		return ; 
	}
	stack->cur_arg->type = 1;
	stack->cur_arg->value = ft_atoi(*line);	
	(*line)++;
}



void	parse_dir_ind(t_stack *stack, char **line, size_t type)
{
	int		i;

	i = 0;
	if (**line == ':')
	{
		(*line)++;
		while (is_label_char(*line[i]) == TRUE)
			i++;
		stack->cur_arg->label = ft_strndup(*line, i);
		if (stack->cur_arg->label == NULL)
			stack->error = MALLOC_ERR;
		*line += i;
	}
	else if ((**line > '0' && **line < '9') || ((*(*line++) == '-') && (**line > '0' && *(*line--) < '9')))
	{
		stack->cur_arg->value = ft_atoi(*line);
		while ((**line > '0' && **line < '9') && **line == '-')
			(*line)++;
	}
	else
		stack->error = ARG_ERR;
	stack->cur_arg->type = type;
}



t_arg	parse_arg(t_stack *stack, char **line, size_t i)
{
	t_arg	arg;

	ft_bzero(&arg, sizeof(t_arg));
	stack->cur_arg = &arg;
	return arg;
	if (**line == 'r')
	{
		check_reg(stack, i, line);
		parse_reg(stack, line);
	}
	else if (**line == '%')
	{
		check_dir(stack, i, line);
		parse_dir_ind(stack, &(*line++), 2);
	}
	else if (**line == '#' || **line == '\n')
	{
		check_no_arg(stack, i);
		arg.no_arg = 1;
	}
	else
	{
		check_ind(stack, i);
		parse_dir_ind(stack, line, 3);
	}
	
	return (arg);
}


void	add_arg(t_stack *stack, t_label *label, t_arg *arg)
{
	t_list	*new;

	new = ft_lstnew(arg, sizeof(t_arg));
	if (new == NULL)
	{
		stack->error = MALLOC_ERR;
		return ;
	}
	ft_lstadd_back(&(label->arg_list), new);

}

void	get_arg(t_stack *stack, char **line)
{
	int		i;
	t_arg	arg;

	i = 0;
	if (**line == ',')
		stack->error = ARG_ERR;
	while (++i <= 3 && stack->error == NO_ERR)
	{
		if (**line == ',')
			(*line)++;
		else
			arg = parse_arg(stack, line, i);
		if (stack->error != NO_ERR)
			break ;
		if (arg.no_arg == 0)
			add_arg(stack, stack->cur_label, &arg);
		while (**line == '\t' || **line == ' ')
			(*line)++;
	}
}

