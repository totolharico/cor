#include "asm.h"
#include "op.h"

void	get_no_name_label(t_stack *stack)
{
	t_list	*new;
	t_label	label;

	ft_bzero(&label, sizeof(t_label));
	new = ft_lstnew(&label, sizeof(t_label));
	if (new == NULL)
		stack->error == MALLOC_ERR;
	else
		ft_lstadd_back(&(stack->label_list), new);
}

void		get_label(t_stack *stack, char **line)
{
	t_list	*new;   
	t_label	label;
    	int		i; 

	i = 0;
	while (is_label_char(*line[i]) == TRUE)
		i++;
	if (*line[i] != ':')
		return (i);
	ft_bzero(&label, sizeof(t_label));
	label.name = ft_strndup(*line, i);
	if (label.name == NULL)
		stack->error == MALLOC_ERR;
	new = ft_lstnew(&label, sizeof(t_label));
	if (new == NULL)
	{
		stack->error == MALLOC_ERR;
		return (i);
	}
	ft_lstadd_back(&(stack->label_list), new);
	stack->cur_label = new;  
	stack->name_label = 1;
	return (i);
}

int8_t	found_op_code(char **line)
{
	char 	*tab[];
	int		i;

	tab = {"live", "ld", "st", "add", "sub", "and", "or",
	"xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"};
	i = 0;
	while(i < 16)
	{
		if (ft_strncmp(*line, tab[i], ft_strlen(tab[i])) == 0)
		{
			*line += ft_strlen(tab[i]);
			return (i + 1);
		}
	}
	return (0);
}

void	found_arg(t_stack *stack, char **line)
{

}

void	get_arg(t_stack *stack, char **line)
{
	if (**line != ' ' && **line != '\t')
	{
		stack->error = OP_ERR;
		return ;
	}
	while (**line == ' ' && **line == '\t')
		*line++;
	while (*line != '\n' && stack->error == NO_ERR)
		found_arg(stack, **line)
}

void	creat_op_list(t_stack *stack, char **line)
{
	t_list		*new;
	t_op		op;

	ft_bzero(&op, sizeof(t_op));
	op.code = found_op_code(line);
	if (op.code == 0)
	{
		stack->error = OP_ERR;
		return ;
	}
	new = ft_lstnew(&op, sizeof(t_op));
	if (new == NULL)
	{
		stack->error == MALLOC_ERR;
		return ;
	}
	ft_lstadd_back(&(stack->cur_label->content->op_list), new);
	get_arg(&op, line);
	

}

void	get_process(t_stack *stack, char *line)
{
	int		i;

	if (*line == '\n')
		return ;
	if (is_label_char(*line) == TRUE)
		i = get_label(stack, &line);
	if (stack->name_label == 0)
		get_no_name_label(stack);
	line += i;
	while (*line == '\t' && *line == ' ')
		line++;
	if (stack->error != NO_ERR)
		return ;
	if (stack->name_label == 0)
		creat_op_list(stack, &line);
}

void	get_name(t_stack *stack, char *line)
{
	int		i;

	i = 0;
	if (ft_strncmp(".name", line, 6) != 0)
		stack->error = NAME_ERR;
	line += 6;
	while (42)
	{
		if (*line != '"')
			stack->error = NAME_ERR;
		line++;
		while (ft_isascii(line[i]) > 0 && line[i] != '"')
			i++;
		if (line[i] == '"' && i <= PROG_NAME_LENGTH)
		{
			stack->name = ft_strndup(line, i);
			if (stack->name == NULL)
				stack->error = MALLOC_ERR;
		}
		else
			stack->error = COMMENT_ERR;
		break ;
	}
	stack->state = GET_STR_COMMENT;
}

void		get_str_comment(t_stack *stack, char *line)
{
	int		i;

	i = 0;
	if (ft_strncmp(".comment ", line, 9) != 0)
		stack->error = NAME_ERR;
	line += 9;
	while (42) 
	{
		if (*line != '"')
			stack->error = COMMENT_ERR;
		line++;
		while (is_label_char(line[i]) == FALSE && *line != '"')
			i++;
		if (i <= COMMENT_LENGTH && line[i] == '"')
		{
			stack->comment = ft_strndup(line, i);
			if (stack->name == NULL)
				stack->error = MALLOC_ERR;
		}
		else
			stack->error = COMMENT_ERR;
		break ;
	}
	stack->state = get_process;
}




int8_t		parser(char *file, t_stack *stack)
{
	static t_parsing	parsing[3] = {get_name, get_comment, get_process};
	char				*line;
	int					ret;
	int					fd;

	if ((fd = open(file, O_RDONLY) == -1))
	stack->state = GET_NAME;
	while (stack->error == NO_ER)
	{
		if ((ret = get_next_line(fd, &line)))
		{
			parsing[stack->state](stack, line);
		}
		else
			break ;
	}

}

int		asm_cor(int ac, char **av)
{
	t_stack		stack;

	ft_bzero(&stack, sizeof(t_stack));
}