#include "../includes/asm.h"
#include "../libft/includes/libft.h"

void	check_no_arg(t_stack *stack, size_t arg)
{
	size_t	op;


	op = stack->cur_label->op_code;
	if (arg == 1
			|| (arg == 2 && (op != 1 && op != 9 && op != 12 && op != 15 && op != 16))
				|| (arg == 3 && (op != 1 && op != 2 && op != 3 && op != 9 && op != 12 && op != 13 && op != 15 && op != 16)))
	{
		stack->error = ARG_ERR;
	}

}

void	check_ind(t_stack *stack, size_t arg)
{
	size_t	op;


	op = stack->cur_label->op_code;
	if ((arg == 1 && (op != 2 && op != 6 && op != 7 && op != 8 && op != 10 && op != 13 && op != 14))
			|| (arg == 2 && (op != 3 && op != 6 && op != 7 && op != 8 && op != 11))
				|| arg == 3)
	{
		stack->error = ARG_ERR;
	}
	
}

void	check_dir(t_stack *stack, size_t arg, char **line)
{
	size_t	op;


	op = stack->cur_label->op_code;
	(*line)++;
	if ((arg == 1 && (op == 3 || op == 4 || op == 5 || op == 11 || op == 16))
			|| (arg == 2 && (op != 6 && op != 7 && op != 8 && op != 10 && op != 11 && op != 14))
				|| (arg == 3 && (op != 11)))
	{
		stack->error = ARG_ERR;
	}

}

void	check_reg(t_stack *stack, size_t arg, char **line)
{
	size_t	op;


	op = stack->cur_label->op_code;
	(*line)++;
	if ((arg == 1 && (op == 1 || op == 2 || op == 9 || op == 12 || op == 13 || op == 15))
			|| (arg == 2 && (op == 1 || op == 9 || op == 12 || op == 15 || op == 16))
				|| (arg == 3 && (op == 1 || op == 2 || op == 3 || op == 9 || op ==  12 || op == 13 || op == 15 || op == 16)))
	{
		stack->error = ARG_ERR;
	}
}
