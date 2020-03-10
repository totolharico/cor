
#include "../includes/asm.h"
#include "../libft/includes/libft.h"

static void		fill_header(t_cor_file *out_file, t_stack *stack)
{
	// write magic number//
	nb_to_binary(out_file, sizeof(COREWAR_EXEC_MAGIC), out_file->total_size, COREWAR_EXEC_MAGIC);
	// write name//
	copy_string(out_file->content, stack->champion_name,  PROG_NAME_LENGTH, &(out_file->total_size));
	// padding //
	copy_string(out_file->content, EMPTY,  PADDING, &(out_file->total_size));
	// Prog size  = 0 pour l'instant + indice de prog size stocke
	// pour s'assurer que c'est pas la taille du programme mais bien son indice//
	out_file->prog_size = out_file->total_size;
	copy_string(out_file->content, EMPTY,  INFO_PROG, &(out_file->total_size));
	//// write comment ///// 
	copy_string(out_file->content, stack->comment,  COMMENT_LENGTH, &(out_file->total_size));
	// padding //
	copy_string(out_file->content, EMPTY,  PADDING, &(out_file->total_size));
}


static int8_t			parser(char *file, t_stack *stack)
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
	if (stack->error != NO_ERR)
		return (-1);;
	return (0);
}



int				main(int ac, char **av)
{
	t_stack		stack;
	t_cor_file	out_file;
	t_label *label;
	int			real_prog_size;
	
	ft_bzero(&stack, sizeof(t_stack));
	stack.oct = 2192;
	if (parser(av[1], &stack) == -1)
	{
		asm_erno(ft_itoa(stack.n_line), stack.error);
		free_all(&stack);
		return (1);
	}
	// while(stack.label_list)
	// {
	// 	label = (t_label*)stack.label_list->content;
	// 	printf("%zu\n", label->oct);
	// 	stack.label_list = stack.label_list->next;
	// }
	if (init_file(&out_file, av[1]) == FALSE)
	{
		free_all(&stack);
		return (1);
	}
	fill_header(&out_file, &stack);
	if (fill_opcode(&out_file, &stack) == FALSE)
	{
		asm_erno("0", LABEL_CALL_ERR);
		free_all(&stack);
		return (1);
	}
	real_prog_size = out_file.total_size - SIZE_HEADER;
	nb_to_binary(&out_file, INFO_PROG, out_file.prog_size, real_prog_size);
	out_file.total_size -= INFO_PROG;
	write(out_file.fd, out_file.content, out_file.total_size);
	ft_printf("Writing output program to %s\n", out_file.name);
	free_all(&stack);
	return (0);
}











