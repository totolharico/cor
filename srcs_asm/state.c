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
	if (**line == '\0' || stack->error != NO_ERR)
		return ;
	while (**line == ' ' || **line == '\t')
		(*line)++;
	get_op(stack, line);
}

void			get_comment(t_stack *stack, char **line)
{
	if (stack->get_tag == 0)
	{
		get_tag_comment(stack, line);
		if (**line == '\0' || **line == '#' || **line == ';' || stack->error != NO_ERR)
			return ;
	}
	parse_name_comment(stack, *line, &stack->comment);
	if (stack->error != NO_ERR)
		return ;
	if (ft_strlen(stack->comment) > 2048)
	{
		stack->error = COMMENT_ERR;
		return ;
	}
	if (stack->in_progress == 0)
		stack->state = GET_PROCESS;
}


void			get_name(t_stack *stack, char **line)
{
	if (stack->get_tag == 0)
	{
		get_tag_name(stack, line);
		if (**line == '\0' || **line == '#' || **line == ';' || stack->error != NO_ERR)
			return ;
	}
	parse_name_comment(stack, *line, &stack->champion_name);
	if (stack->error != NO_ERR)
		return ;
	if (ft_strlen(stack->champion_name) > 128)
	{
		stack->error = NAME_ERR;
		return ;
	}
	if (stack->in_progress == 0)
	{
		stack->state = GET_COMMENT;
		stack->get_tag = 0;
	}
}












