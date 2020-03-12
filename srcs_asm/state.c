#include "../includes/asm.h"
#include "../libft/includes/libft.h"

static void			get_arg(t_stack *stack, char **line)
{
	int		i;
	t_arg	arg;

	i = 0;
	if (**line == ',')
		stack->error = ARG_ERR;
	while (++i <= 3 && stack->error == NO_ERR)
	{
		if (**line == ',')
		{
			(*line)++;
			if (**line == '\0')
			{
				stack->error = ARG_ERR;
				break;
			}
		}
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


static void			get_op(t_stack *stack, char **line)
{
	stack->cur_label->op_code = found_op_code(line);
	update_oct(stack, stack->cur_label->op_code);
	if (stack->cur_label->op_code == 0)
	{
		stack->error = OP_ERR;
		return ;
	}
	if (**line != ' ' && **line != '\t')
	{
		stack->error = OP_ERR;
		return ;
	}
	while (**line == ' ' || **line == '\t')
		(*line)++;
	get_arg(stack, line);
	
}


void			get_process(t_stack *stack, char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (**line == '\0' || **line == '#' || **line == ';')
		return ;
	label(stack, line);
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (**line == '\0' || **line == '#' || **line == ';' || stack->error != NO_ERR)
		return ;
	get_op(stack, line);
	check_end(stack, *line);
}

static void				get_tag(t_stack *stack, char **line)
{
	if (cmp_tag(line, ".name") == TRUE && !stack->champion_name)
	{
		stack->get_name = 1;
		parse_name_comment(stack, line, &stack->champion_name, &stack->get_name);
		if (ft_strlen(stack->champion_name) > 128)
			stack->error = NAME_ERR;
	}
	else if (cmp_tag(line, ".comment") == TRUE && !stack->comment)
	{
		stack->get_comment = 1;
		parse_name_comment(stack, line, &stack->comment, &stack->get_comment);
		if (ft_strlen(stack->comment) > 2048)
			stack->error = COMMENT_ERR;
	}
	else
		stack->error = TAG_ERR;
}

void				get_name_or_comment(t_stack *stack, char **line)
{
	if (!stack->get_tag)
	{
		while (**line == ' ' || **line == '\t')
			(*line)++;
		if (**line == '\0' || **line == '#' || **line == ';')
			return ;
		get_tag(stack, line);
		if (stack->comment && stack->champion_name && !stack->in_progress)
			stack->state = GET_PROCESS;
		return ;
	}
	if (stack->get_name)
	{
		parse_name_comment(stack, line, &stack->champion_name, &stack->get_name);
		if (ft_strlen(stack->champion_name) > 128)
			stack->error = NAME_ERR;
	}
	else if (stack->get_comment)
	{
		parse_name_comment(stack, line, &stack->comment, &stack->get_comment);
		if (ft_strlen(stack->comment) > 2048)
			stack->error = COMMENT_ERR;
	}
	if (stack->comment && stack->champion_name && !stack->in_progress)
		stack->state = GET_PROCESS;
}









