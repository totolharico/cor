
#include "../includes/asm.h"
#include "../libft/includes/libft.h"

static int		is_label_char(char c)
{
	char		*tab;

	tab = "abcdefghijklmnopqrstuvwxyz_0123456789";
	while (*tab)
	{
		if (c == *tab)
			return (1);
		tab++;
	}
	return (0);
}

void			label(t_stack *stack, char **line)
{
	t_list		*new;
	t_label		label;
	int			i;

	i = 0;
	ft_bzero(&label, sizeof(t_label));
	while (is_label_char((*line)[i]) == 1)
		i++;
	if ((*line)[i++] == ':')
	{
		label.name = ft_strndup(*line, --i);
		*line += (i + 1);
		if (label.name == NULL)
			stack->error = MALLOC_ERR;
	}
	label.oct = stack->oct;
	new = ft_lstnew(&label, sizeof(t_label));
	if (new == NULL || stack->error != NO_ERR)
	{
		stack->error = MALLOC_ERR;
		return ;
	}
	ft_lstadd_back(&(stack->label_list), new);
	stack->cur_label = (t_label*)new->content;
}

void			init_tab(char *tab[16])
{
	tab[0] = "live";
	tab[1] = "ld";
	tab[2] = "st";
	tab[3] = "add";
	tab[4] = "sub";
	tab[5] = "and";
	tab[6] = "or";
	tab[7] = "xor";
	tab[8] = "zjmp";
	tab[9] = "ldi";
	tab[10] = "sti";
	tab[11] = "fork";
	tab[12] = "lld";
	tab[13] = "lldi";
	tab[14] = "lfork";
	tab[15] = "aff";
}					

int8_t			found_op_code(char **line)
{
	char 	*tab[16];
	int		i;
	int		j;


	init_tab(tab);
	i = 0;
	j = 0;
	while ((*line)[j] != ' ' && (*line)[j] != '\t' && (*line)[j] != '\0')
		j++;
	while(i < 16)
	{
		if (ft_strncmp(*line, tab[i], j) == 0)
		{
			(*line) += j;
			return (i + 1);
		}
		i++;
	}
	return (0);
}


void    update_oct(t_stack *stack, size_t op)
{    
	if (op != 1 && op != 9 && op != 12 && op != 15)
		stack->cur_label->encod_b = 1;
	stack->oct = stack->cur_label->encod_b + 1;
}


void			get_op(t_stack *stack, char **line)
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
	while (**line == '\t' || **line == ' ')
		(*line)++;
	if (**line == '\0' || **line == '#')
		return ;
	label(stack, line);
	if (**line == '\0' || stack->error != NO_ERR)
		return ;
	get_op(stack, line);
}

int				count_name_comment(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n' && str[i] != '#')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i--;
	return (i);
}

void			get_name(t_stack *stack, char **line)
{
	int		i;

	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (**line == '\n')
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

void			get_comment(t_stack *stack, char **line)
{
	int		i;

	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (**line == '\n')
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




int8_t			parser(char *file, t_stack *stack)
{
	static t_parsing	parsing[3] = {get_name, get_comment, get_process};
	char				*line;
	int					ret;
	int					fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		stack->error = FILE_ERR;
	stack->state = GET_NAME;
	while (stack->error == NO_ERR)
	{
		stack->n_line++;
		if ((ret = get_next_line(fd, &line)) > 0)
			parsing[stack->state](stack, &line);
		else if (ret == -1)
			stack->error = READ_ERR;
		else
			break ;
	}
	if ()
	//printf("%s\n", stack->cur_label->name);
	
	return (1);
}

int				main(int ac, char **av)
{
	t_stack		stack;
	t_list		*label_list;
	t_list		*arg_list;
	t_arg       *arg;
	t_label     *label;

	ft_bzero(&stack, sizeof(t_stack));
	stack.oct = 2192;
	parser(av[1], &stack);
	printf("name:%s\n", stack.champion_name);
	printf("comment:%s\n", stack.comment);
	
	label_list = stack.label_list;
	
	while (label_list)
	{
		printf("\n");
		label = (t_label*)label_list->content;
		printf("label:%s\n", label->name);
		printf("opcode:%zu\n", label->op_code);
		arg_list = label->arg_list;
		while (arg_list)
		{
			arg = (t_arg*)arg_list->content;
			printf("labelcall:%s\n", arg->label);
			printf("type:%zu\n", arg->type);
			printf("value:%d\n", arg->value);
			printf("\n");
			arg_list = arg_list->next;
		}
		label_list = label_list->next;
	}
	return (0);
}











