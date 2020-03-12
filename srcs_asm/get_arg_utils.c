#include "../includes/asm.h"
#include "../libft/includes/libft.h"

void	parse_reg(t_stack *stack, char **line, t_arg *arg)
{
	int		nb;

	nb = ft_atoi(*line);
	if (nb < 0 && nb > 16)
	{
		stack->error = ARG_ERR;
		return ; 
	}
	arg->type = 1;
	arg->value = nb;
	(*line)++;
}

static int		ft_atolong(char *str, t_arg *arg)
{
	long	neg;
	long	nb;
	long	bits;

	neg = 1;
	nb = 0;
	bits = 0;
	while (*str == ' ' || *str == '\f' || *str == '\t'
			|| *str == '\n' || *str == '\r' || *str == '\v')
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit((long)*str))
	{
		nb = 10 * nb + *str - 48;
		bits = count_bits(nb);
		if (bits >= 63)
		{
			arg->value = 4294967294;
			return (TRUE);
		}
		str++;
	}
	arg->value = nb * neg;
	return (TRUE);
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
	else if ((**line >= '0' && **line <= '9') || (((*(*line)++) == '-') && (**line >= '0' && (*(*line)--) <= '9')))
	{
		arg->value = ft_atolong(*line, arg);
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
	else if (**line == '#' || **line == '\0' || **line == ';')
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





