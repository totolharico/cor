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
	int		i;

	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (**line == '\0')
		return ;
	if (ft_strncmp(".comment", *line, 8) != 0)
	{
		stack->error = COMMENT_ERR;
		return ;
	}
	*line += 8;
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (*(*line)++ != '"')
		stack->error = COMMENT_ERR;
	i = count_name_comment(*line);
	if ((*line)[i] != '"' && i > 2048 && stack->error != NO_ERR)
	{
		stack->error = COMMENT_ERR;
		return ;
	}
	stack->comment = ft_strndup(*line, --i);
	if (stack->comment == NULL)
		stack->error = MALLOC_ERR;
	stack->state = GET_PROCESS;
}


void			get_name(t_stack *stack, char **line)
{
	int		i;

	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (**line == '\0')
		return ;
	if (ft_strncmp(".name", *line, 5) != 0)
	{
		stack->error = NAME_ERR;
		return ;
	}
	*line += 5;
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (*(*line)++ != '"')
		stack->error = NAME_ERR;
	i = count_name_comment(*line);
	if ((*line)[i] != '"' && i > 128 && stack->error != NO_ERR)
	{
		stack->error = NAME_ERR;
		return ;
	}
	stack->champion_name = ft_strndup(*line, --i);
	if (stack->champion_name == NULL)
		stack->error = MALLOC_ERR;
	stack->state = GET_COMMENT;
}
