#include "../includes/asm.h"
#include "../libft/includes/libft.h"

void			get_tag_comment(t_stack *stack, char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (**line == '\0' || **line == '#' || **line == ';')
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
	stack->get_tag = 1;
}

void			get_tag_name(t_stack *stack, char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (**line == '\0' || **line == '#' || **line == ';')
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
	stack->get_tag = 1;
}

void				parse_name_comment(t_stack *stack, char *str, char **str2)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '#' && str[i] != ';')
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	if (count % 2 == 0)
		stack->in_progress = 1;
	else
	{
		while (str[i] == ' ' || str[i] == '\t')
			i--;
		str[--i] = '\0';
		stack->in_progress = 0;
	}
	*str2 = *str2 == NULL ? ft_strdup(str) : ft_strjoin(*str2, str);
	if (*str2 != NULL && stack->in_progress == 1)
		*str2 = ft_strjoin(*str2, "\n");
	if (*str2 == NULL)
		stack->error = MALLOC_ERR;
	return ;
}