#include "../includes/asm.h"
#include "../libft/includes/libft.h"

static void			get_str2(char **str, char **str2, int in_progress)
{
	char 	*tmp;

	tmp = *str2;
	*str2 = *str2 == NULL ? ft_strdup(*str) : ft_strjoin(*str2, *str);
	if (tmp)
		free(tmp);
	tmp = *str2;
	if (*str2 != NULL && in_progress == 1)
		*str2 = ft_strjoin(*str2, "\n");
	if (tmp)
		free(tmp);
}

static void			put_mark(t_stack *stack, int mark)
{
	stack->get_tag = mark;
	stack->in_progress = mark;
}

void			parse_name_comment(t_stack *stack, char **str, char **str2, int *mark)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while ((*str)[++i] && (*str)[i] != '#' && (*str)[i] != ';')
		if ((*str)[i] == '"')
			count++;
	if (count % 2 == 0)
		put_mark(stack, 1);
	else
	{
		while ((*str)[i] != '"')
			i--;
		check_end(stack, ((*str) + i + 1));
		(*str)[i--] = '\0';
		if (stack->error != NO_ERR)
			return ;
		put_mark(stack, 0);
		*mark = 0;
	}
	get_str2(str, str2, stack->in_progress);
	if (*str2 == NULL)
		stack->error = MALLOC_ERR;
	return ;
}

int					cmp_tag(char **line, char *str)
{
	if (ft_strncmp(str, *line, ft_strlen(str)))
		return (FALSE);
	(*line) += ft_strlen(str);
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (**line != '"')
		return (FALSE);
	(*line)++;
	return (TRUE);
}
