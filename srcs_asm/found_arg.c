
void	arg_reg(t_stack *stack, size_t arg, char **line)
{
	size_t	op;


	op = stack->curent_op->op_code;
	if ((arg == 1 && (op == 1 || op == 2 || op == 9 || op == 12 || op == 13 || op == 15))
			|| (arg == 2 && (op == 1 || op == 9 || op == 12 || op == 15 || op == 16))
				|| (arg == 3 && (op == 1 || op == 2 || op == 3 || op == 9 || op ==  12 || op == 13 || op == 15 || op == 16)))
	{
		stack->error = OP_ERR;
		return ;
	}
	if (*line < '0' && *line > '5')
	{
		stack->error = OP_ERR;
		return ; 
	}
	*line++;
}

void	get_arg(t_stack *stack, char **line)
{
	int		i;
	t_arg	arg;
	t_list	*new;

	i = 0; 
	ft_bzero(&arg, sizeof(t_arg));
	while (++i < 3)
	{
		if (**line == 'r' && arg_reg(stack, i, line) == SUCCES)
		{
			ar
		}
		else if (**line == '%')

	}
}