/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_code_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:48:14 by dberger           #+#    #+#             */
/*   Updated: 2020/03/03 20:14:12 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/includes/libft.h"

// int		find_opcode(char *string)
// {
// 	int		i;

// 	i = 0;
// 	while (i < 16)
// 	{
// 		if (!ft_strcmp(string, g_op_tab[i].name))
// 			return (i + 1);
// 		i++;
// 	}
// 	return (0);
// }

int		encoding_byte(t_label *label)
{
	int			i;
	int			k;
	t_arg		*arg;

	i = 0;
	k = 0;
	while (label->arg_list)
	{
		k++;
		arg = (t_arg*)label->arg_list->content;
		i = i | arg->type;
		i = i << 2;
		label->arg_list = label->arg_list->next;
	}
	while (k < (BITS_IN_OCTET / 2) - 1)
	{
		i = i | 0;
		i = i << 2;
		k++;
	}
	return (i);
}

static int		find_label(char *to_find, t_list *label_list)
{
	t_label 	*label;
	int			oct_lab;

	oct_lab = 0;
	while (label_list != NULL)
	{
		label = (t_label*)label_list->content;
		if (!ft_strcmp(label->name, to_find))
		{
			printf("%s\n", label->name);
			printf("%zu\n", label->oct);
			return (label->oct);
		}
		label_list = label_list->next;
	}
	return (FALSE);
}

int		write_op_values(t_cor_file *out_file, int *i, t_label *label, t_stack stack)
{
	t_arg	*arg;
	t_list	*arg_list;
	int		to_label;
	int		oct;

	to_label = 0;
	oct = 0;
	arg_list = label->arg_list;
	printf("%s\n", label->name);
	printf("%zu\n", label->op_code);
	while (arg_list)
	{	
		
		arg = (t_arg*)arg_list->content;
		if (arg->type == 1)
		{
			write_in_file(out_file, *i, arg->value);
		}
		else if (arg->label == NULL)
		{
			nb_to_binary(out_file, arg->oct, *i, arg->value);
		}
		else if (arg->label != NULL)
		{
			to_label = find_label(arg->label, stack.label_list);
			if (to_label == FALSE)
				return (FALSE);
			nb_to_binary(out_file, arg->oct, *i, (to_label - label->oct));
		}
		*i += arg->oct;
		arg_list = arg_list->next;
	}
	return (TRUE);
}
