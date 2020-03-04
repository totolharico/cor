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

void	parse_reg(t_stack *stack, char **line, t_arg *arg)
{
	if (**line < '0' && **line > '5')
	{
		stack->error = ARG_ERR;
		return ; 
	}
	arg->type = 1;
	arg->value = ft_atol(*line);
	(*line)++;
}



void	parse_dir_ind(t_stack *stack, char **line, t_arg *arg)
{
	int		i;

	i = 0;
	if (**line == ':')
	{
		(*line)++;
		while (is_label_char((*line)[i]) == TRUE)
			i++;
		arg->label = ft_strndup(*line, i);
		if (arg->label == NULL)
			stack->error = MALLOC_ERR;
		*line += i;
	}
	else if ((**line >= '0' && **line <= '9') || ((*(*line++) == '-') && (**line >= '0' && *(*line--) <= '9')))
	{
		arg->value = ft_atol(*line);
		while ((**line >= '0' && **line <= '9') || **line == '-')
			(*line)++;
	}
	else
		stack->error = ARG_ERR;
}



t_arg	parse_arg(t_stack *stack, char **line, size_t i)
{
	t_arg	arg;

	ft_bzero(&arg, sizeof(t_arg));
	if (**line == 'r')
	{
		check_reg(stack, i, line);
		parse_reg(stack, line, &arg);
	}
	else if (**line == '%')
	{
		check_dir(stack, i, line);
		parse_dir_ind(stack, &(*line++), &arg);
		arg.type = 2;
	}
	else if (**line == '#' || **line == '\0')
	{
		check_no_arg(stack, i);
		arg.no_arg = 1;
	}
	else
	{
		check_ind(stack, i);
		parse_dir_ind(stack, line, &arg);
		arg.type = 3;
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

void	add_oct(t_stack *stack, t_arg *arg)
{
	size_t	op;

	op = stack->cur_label->op_code;
	if (arg->type == 0)
		return ;
	if (arg->type == 1)
		arg->oct = 1;
	else if (arg->type == 3)
		arg->oct = 2;
	else if (arg->type == 2 && (op == 9 || op == 10 || op == 11 || op == 12 || op == 14 || op == 15))
		arg->oct = 2;
	else
		arg->oct = 4;
	stack->oct += arg->oct;
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
		while (**line == '\t' || **line == ' ')
			(*line)++;
		arg = parse_arg(stack, line, i);
		if (stack->error != NO_ERR)
			break ;
		add_oct(stack, &arg);
		if (arg.no_arg == 0)
			add_arg(stack, stack->cur_label, &arg);
		
	}
}





