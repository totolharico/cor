#ifndef ASM_H
# define ASM_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/includes/libft.h"
# include <stdint.h>
# include <limits.h>

/*
*****************
***** ERROR *****
*****************
*/

/*
**** Generic error
*/

# define NO_ERR				0x00000000
# define NAME_ERR			0x00000001

/*
**** name error
*/

# define COMMENT_ERR			0x00000010

/*
**** Rooms error
*/

// # define INVALID_COORD		0x00000040
// # define BAD_START_LETTER	0x00000080
// # define MISS_ROOMS			0x00000100
// # define SAME_NAME			0x00000200
// # define SAME_COORD			0x00000400
// # define START_ROOM			0x00000800
// # define END_ROOM			0x00001000
// # define TOO_FEW			0x00002000
// # define UNKNOW_ROOM		0x00004000

// /*
// **** Type of errors
// */

# define OP_ERR				0x00010000
# define ARG_ERR			0x00020000


/*
**** Critical errors
*/

# define READ_ERR			0x10000000
# define MALLOC_ERR			0x20000000
# define WRITE_ERR			0x40000000
# define FILE_ERR			0x80000000

# define IND_SIZE     2
# define REG_SIZE     4
# define DIR_SIZE     REG_SIZE

/*
**** op_code
*/


enum				e_state
{
	GET_NAME,
	GET_COMMENT,
	GET_PROCESS,
};

typedef struct 		s_arg
{
	char			*label;
	size_t			type;
	size_t			oct;
	size_t			no_arg;
	int				value;
}					t_arg;


typedef struct 		s_label
{
	char			*name;
	size_t			oct;
	size_t			op_code;
	t_list			*arg_list;
}					t_label;


typedef struct		s_stack
{
	char			*champion_name;
	uint32_t		error;
	size_t			oct;
	enum e_state	state;
	char			*comment;
	t_label			*cur_label;
	t_arg			*cur_arg;
	t_list			*label_list;
}					t_stack;


typedef void		(*t_parsing)(t_stack *, char **);
void				get_name(t_stack *stack, char **line);
void				get_comment(t_stack *stack, char **line);
void				get_process(t_stack *stack, char **line);

int					asm_cor(int ac, char **av);

void				get_arg(t_stack *stack, char **line);
t_arg				parse_arg(t_stack *stack, char **line, size_t i);
void				check_no_arg(t_stack *stack, size_t arg);
void				check_ind(t_stack *stack, size_t arg);
void				check_dir(t_stack *stack, size_t arg, char **line);
void				check_reg(t_stack *stack, size_t arg, char **line);


#endif







