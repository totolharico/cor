
#include "asm.h"
#include "op.h"

void	label(t_stack *stack, char **line)
{
	t_list	*new;   
	t_label	label;
	int		i; 

	i = 0;
	ft_bzero(&label, sizeof(t_label));
	new = ft_lstnew(&label, sizeof(t_label));
	while (is_label_char(*line[i]) == TRUE)
		i++;
	if (*line[i++] == ':')
	{
		label.name = ft_strndup(*line, i);
		*line += i;
		if (label.name == NULL)
			stack->error = MALLOC_ERR;
	}
	if (new == NULL || stack->error != NO_ERR)
	{
		stack->error == MALLOC_ERR;
		return ;
	}
	ft_lstadd_back(&(stack->label_list), new);
	stack->cur_label = new;
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


void	get_op(t_stack *stack, char **line)
{
	stack->cur_label->op_code = found_op_code(line);
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
	while (**line == ' ' && **line == '\t')
		*line++;
	get_arg(stack, line);
	
}

void	get_process(t_stack *stack, char **line)
{
	while (**line == '\t' && **line == ' ')
		(*line)++;
	if (**line == '\n')
		return ;
	label(stack, line);
	if (stack->error != NO_ERR)
		return ;
	get_op(stack, &line);
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