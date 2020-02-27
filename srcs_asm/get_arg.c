
void	add_arg(t_op *op, t_arg *arg)
{
	t_list	*new;

	new = ft_lstnew(arg, sizeof(t_arg));
	if (new == NULL)
	{
		stack->error = MALLOC_ERR;
		return ;
	}
	ft_lstadd_back(&(stack->curent_label->arg_list), new);

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
			&arg = parse_arg(stack, i, *line);
		if (stack->error != NO_ERR)
			break ;
		if (&arg != NULL)
			add_arg(stack->curent_op);
		while (**line == '\t' && **line == ' ')
			(*line)++;
	}
}







