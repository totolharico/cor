#include "../includes/asm.h"
#include "../libft/includes/libft.h"

static void		free_node(void *content)
{
	free(content);
}

void		free_all(t_stack *stack)
{
	t_list	*label_list;
	t_list	*arg_list;
	t_label	*label;
	t_arg	*arg;

	label_list = stack->label_list;
	if (stack->champion_name)
		free(stack->champion_name);
	if (stack->comment)
		free(stack->comment);
	while (label_list)
	{
		label = (t_label*)label_list->content;
		arg_list = label->arg_list;
		while (arg_list)
		{
			arg = (t_arg*)arg_list->content;
			ft_lstdelnode(&arg_list, arg, &free_node);
		}
		ft_lstdelnode(&label_list, label, &free_node);
	}
}