#ifndef ASM_H
# define ASM_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/includes/libft.h"
# include "op.h"
# include <stdint.h>
# include <limits.h>



# define TRUE				1
# define FALSE				0

# define NO_ERR				0x00000000
# define TAG_ERR			0x00000001
# define BAD_COMMENT		0x00000002
# define MISSING_QUOTE		0x00000004

# define NAME_ERR			0x00000010
# define COMMENT_ERR		0x00000020



# define OP_ERR				0x00010000
# define ARG_ERR			0x00020000
# define SOURCE_FILE_ERR	0x00040000
# define LABEL_CALL_ERR		0x00080000


# define READ_ERR			0x10000000
# define MALLOC_ERR			0x20000000
# define FILE_ERR			0x80000000

# define IND_SIZE     		2
# define REG_SIZE     		4
# define DIR_SIZE     		REG_SIZE


# define PROG_ASM			0
# define MAX_SIZE_FILE		2875
# define SIZE_HEADER		2192
# define BITS_IN_OCTET		8
# define PADDING			4
# define INFO_PROG			4
# define EMPTY				"\0"
# define MAX_ARGS			3
# define ALT_COMMENT_CHAR   ';'


enum				e_state
{
	GET_NAME_COMMENT,
	GET_PROCESS,
};

typedef struct 		s_arg
{
	char			*label;
	size_t			type;
	size_t			oct;
	size_t			no_arg;
	long			value;
}					t_arg;


typedef struct 		s_label
{
	char			*name;
	size_t			oct;
	size_t			encod_b;
	size_t			op_code;
	t_list			*arg_list;
}					t_label;


typedef struct		s_stack
{
	char			*champion_name;
	uint32_t		error;
	size_t			oct;
	int				in_progress;
	int				get_tag;
	int				get_name;
	int				get_comment;
	int				n_line;
	enum e_state	state;
	char			*comment;
	t_label			*cur_label;
	t_list			*label_list;
}					t_stack;

typedef struct 		s_cor_file
{
	int				fd;
	char			*name;
	char			*content;
	int				total_size;
	int				prog_size;
}					t_cor_file;


int					main(int ac, char **av);


typedef void		(*t_parsing)(t_stack *, char **);
void				get_name_or_comment(t_stack *stack, char **line);
void				get_process(t_stack *stack, char **line);


void				parse_name_comment(t_stack *stack, char **str, char **str2, int *mark);
int					cmp_tag(char **line, char *str);



void				label(t_stack *stack, char **line);
int					is_label_char(char c);
void    			update_oct(t_stack *stack, size_t op);
int8_t				found_op_code(char **line);


t_arg				parse_arg(t_stack *stack, char **line, size_t i);
void				parse_dir_ind(t_stack *stack, char **line, t_arg *arg);
void				parse_reg(t_stack *stack, char **line, t_arg *arg);
void				add_arg(t_stack *stack, t_label *label, t_arg *arg);
void				add_oct(t_stack *stack, t_arg *arg);


void				check_no_arg(t_stack *stack, size_t arg);
void				check_ind(t_stack *stack, size_t arg);
void				check_dir(t_stack *stack, size_t arg, char **line);
void				check_reg(t_stack *stack, size_t arg, char **line);


void				asm_erno(char *line, uint32_t error);


int					init_file(t_cor_file *out_file, char *source_file);


int					fill_opcode(t_cor_file *out_file, t_stack *stack);

void				free_all(t_stack *stack);

char				*ft_stricat(char *dest, const char *src, int indx_dest);
void				check_end(t_stack *stack, char *line);
void				nb_to_binary(t_cor_file *out_file, int octets, int indx, long nb);
long				count_bits(long nb);
void				write_in_file(t_cor_file *out_file, int indx, int n);
void				copy_string(char *dest, char *src, int size, int *indx);



#endif







