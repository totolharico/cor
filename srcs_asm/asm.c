
#include "../includes/asm.h"
#include "../libft/includes/libft.h"

static int		is_label_char(char c)
{
	char	*tab;

	tab = "abcdefghijklmnopqrstuvwxyz_0123456789";
	while (*tab)
	{
		if (c == *tab)
			return (1);
		tab++;
	}
	return (0);
}

void	label(t_stack *stack, char **line)
{
	t_list	*new;
	t_label	label;
	int		i; 

	i = 0;
	ft_bzero(&label, sizeof(t_label));
	while (is_label_char(*line[i]) == 1)
		i++;
	if (*line[i++] == ':')
	{
		label.name = ft_strndup(*line, i);
		*line += i;
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
	stack->cur_label = &label;
}

void	init_tab(char *tab[16])
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

int8_t	found_op_code(char **line)
{
	char 	*tab[16];
	int		i;


	init_tab(tab);
	i = 0;
	while(i < 16)
	{
		if (ft_strncmp(*line, tab[i], ft_strlen(tab[i])) == 0)
		{
			(*line) += ft_strlen(tab[i]);
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
		(*line)++;
	get_arg(stack, line);
	
}

void	get_process(t_stack *stack, char **line)
{
	while (**line == '\t' && **line == ' ')
		(*line)++;
	if (**line == '\n')
		return ;
	label(stack, line);
	if (**line == '\n')
		return ;
	if (stack->error != NO_ERR)
		return ;
	get_op(stack, line);
}

void	get_name(t_stack *stack, char **line)
{
	int		i;

	i = 0;
	while (**line == ' ' && **line == '\t')
		(*line)++;
	if (**line == '\n')
		return ;
	if (ft_strncmp(".name", *line, 5) != 0)
	{
		stack->error = NAME_ERR;
		return ;
	}
	*line += 6;
	while (**line == ' ' && **line == '\t')
		(*line)++;
	if (*(*line++) != '"')
		stack->error = NAME_ERR;
	while (ft_isascii(*line[i]) > 0 && *line[i] != '"')
		i++;
	while (*line[i] == '"')
		i++;
	i--;
	if (*line[i] != '"' && i > 128)
		stack->error = NAME_ERR;
	stack->champion_name = ft_strndup(*line, --i);
	if (stack->champion_name == NULL)
		stack->error = MALLOC_ERR;
	stack->state = GET_COMMENT;

}

void		get_comment(t_stack *stack, char **line)
{
	int		i;

	i = 0;
	printf("%s\n", "coucou");
	while (**line == ' ' && **line == '\t')
		(*line)++;
	if (**line == '\n')
		return ;
	if (ft_strncmp(".comment ", *line, 9) != 0)
		stack->error = COMMENT_ERR;
	line += 9;
	while (**line == ' ' && **line == '\t')
		(*line)++;
	if (*(*line++) != '"')
		stack->error = COMMENT_ERR;
	while (ft_isascii(*line[i]) > 0 && *line[i] != '"')
		i++;
	while (*line[i] == '"')
		i++;
	i--;
	if (*line[i] != '"' && i > 2048)
		stack->error = COMMENT_ERR;
	stack->comment = ft_strndup(*line, --i);
	if (stack->comment == NULL)
		stack->error = MALLOC_ERR;
	stack->state = GET_PROCESS;
	
}




int8_t		parser(char *file, t_stack *stack)
{
	static t_parsing	parsing[3] = {get_name, get_comment, get_process};
	char				*line;
	int					ret;
	int					fd;

	if ((fd = open(file, O_RDONLY) == -1))
		stack->error = FILE_ERR;
	printf("fd:%d\n", fd);
	stack->state = GET_NAME;
	while (stack->error == NO_ERR)
	{
		if ((ret = get_next_line(fd, &line)) > 0)
		{
			printf("line:%s\n", line);
			parsing[stack->state](stack, &line);
		}
		else if (ret == -1)
			stack->error = READ_ERR;
		else
			break ;
	}
	
	return (1);
}

int		main(int ac, char **av)
{
	t_stack		stack;

	ft_bzero(&stack, sizeof(t_stack));
	stack.oct = 2192;
	parser(av[1], &stack);
	printf("%s\n", stack.champion_name);
	return (0);
}











