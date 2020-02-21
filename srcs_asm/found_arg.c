
int8_t	check_op(size_t op, size_t arg, size_t type)
{

	if (type == 1 && arg == 1 && (op == 1 || op == 2 || op == 6 || op ==  ||))
	 ar
	else if (op == 2 || op == 13)
	
	else if (op == 3)
	
	else if (op == 4 || op == 5)

	else if (op == 6 || op == 7 || op == 8)
	
	else if (op == 10 || op == 14)
	
	else if (op == 11)

	else 
}

void	found_arg(t_stack *stack, char **line)
{
	static	t_func_arg func_arg[3] = {arg_1, arg_2, arg_3}
	size_t	op;
	int		i;

	i = 0; 
	op = stack->curent_op->code;
	while (++i < 3)
	{
		if (*line++ == 'r' && *line < 5 && *line > 0)
			type = 1
		else if (--(*line) == '%')
		if (func_arg[i](op, type) == 0)
			return ;
	}


}