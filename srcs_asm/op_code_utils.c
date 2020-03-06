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

static int		encoding_byte(t_label *label)
{
	int			i;
	int			k;
	t_list		*arg_list;
	t_arg		*arg;

	i = 0;
	k = 0;
	arg_list = label->arg_list;
	while (arg_list)
	{
		k++;
		arg = (t_arg*)arg_list->content;
		i = i | arg->type;
		i = i << 2;
		arg_list = arg_list->next;
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
		if (label->name != NULL && !ft_strcmp(label->name, to_find))
			return (label->oct);
		label_list = label_list->next;
	}
	return (FALSE);
}

static int		write_op_values(t_cor_file *out_file, int *i, t_label *label, t_stack *stack)
{
	t_arg		*arg;
	t_list		*arg_list;
	int			to_label;

	to_label = 0;
	arg_list = label->arg_list;
	while (arg_list)
	{	
		arg = (t_arg*)arg_list->content;
		if (arg->type == 1)
			write_in_file(out_file, *i, arg->value);
		else if (arg->label == NULL)
			nb_to_binary(out_file, arg->oct, *i, arg->value);
		else if (arg->label != NULL)
		{
			to_label = find_label(arg->label, stack->label_list);
			if (to_label == FALSE)
				return (FALSE);
			nb_to_binary(out_file, arg->oct, *i, (to_label - label->oct));
		}
		*i += arg->oct;
		arg_list = arg_list->next;
	}
	return (TRUE);
}

int				fill_opcode(t_cor_file *out_file, t_stack *stack)
{
	t_list		*label_list;
	t_label		*label;
	int			i;

	label_list = stack->label_list;
	i = out_file->total_size;
	while (label_list != NULL)
	{
		label = (t_label*)label_list->content;
		if (label->op_code != 0)
		{
			write_in_file(out_file, i, label->op_code);
			if (label->encod_b)
				write_in_file(out_file, ++i, encoding_byte(label));
			i++;
			if (write_op_values(out_file, &i, label, stack) == FALSE)
				return (FALSE);
		}
		label_list = label_list->next;
	}
	return (TRUE);
}
