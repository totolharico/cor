#include "../includes/asm.h"
#include "../libft/includes/libft.h"

 
void	parse_reg(t_arg *arg, char **line)
{
	if (**line < '0' && **line > '5')
	{
		stack->error = ARG_ERR;
		return ; 
	}
	arg->type = 1;
	arg->value = ft_atoi(*line);	
	*line++;
}



void	parse_dir_ind(t_arg *arg, char **line, size_t type)
{
	int		i;

	i = 0;
	if (**line == ':')
	{
		*line++;
		while (is_label_char(*line[i]) == TRUE)
			i++;
		arg->label = ft_strndup(*line, i);
		if (arg->label == NULL)
			stack->error = MALLOC_ERR;
		*line += i;
	}
	else if ((**line > '0' && **line < '9') || (*(*line++) == '-') && (**line > '0' && *(*line--) < '9'))
	{
		arg->value = ft_atoi(*line);
		while ((**line > '0' && **line < '9') && **line == '-')
			*line++;
	}
	else
		stack->error = ARG_ERR;
	arg->type = type;
}



t_arg	parse_arg(t_stack *stack, char **line, size_t i)
{
	t_arg	arg;

	ft_bzero(&arg, sizeof(t_arg));
	if (**line == 'r')
	{
		check_reg(stack, i);
		parse_reg(&arg, &(*line++));
	}
	else if (**line == '%')
	{
		check_dir(stack, i);
		parse_dir_ind(&arg, &(*line++), 2);
	}
	else if (**line == '#' || **line == '\n')
	{
		check_no_arg(stack, i);
		&arg = NULL;
	}
	else
	{
		check_ind(stack, i);
		parse_dir_ind(&arg, line, 3);
	}
	return (arg);
}


void	add_arg(t_label *label, t_arg *arg)
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
	while (++i <= 3 && stack->error == NO_ERR)
	{
		if (**line == ',')
			*line++;
		else
			arg = parse_arg(stack, i, *line);
		if (stack->error != NO_ERR)
			break ;
		if (&arg != NULL)
			add_arg(stack->curent_label, &arg);
		while (**line == '\t' && **line == ' ')
			(*line)++;
	}
}

