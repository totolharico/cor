#ifndef ASM_H
# define ASM_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
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
# define BAD_FORMAT			0x00000001

/*
**** name error
*/

# define NAME_ERR			0x00000010

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

// # define ANTS_ERR			0x00010000
// # define ROOMS_ERR			0x00020000
// # define LINKS_ERR			0x00040000
// # define PRE_PROCESS_ERR	0x00100000
// # define PROCESS_ERR		0x00200000

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

# define LIVE 				0x01
# define LD 				0x02
# define ST 				0x03
# define ADD 				0x04
# define SUB 				0x05
# define AND				0x06
# define OR					0x07
# define XOR 				0x08
# define ZJMP 				0x09
# define LDI 				0x0a
# define STI 				0x0b
# define FORK 				0x0c
# define LLD1 				0x0d
# define LLDI 				0x0e
# define LFORK 				0x0f
# define AFF 				0x10


enum				e_state
{
	GET_NAME,
	GET_COMMENT,
	GET_PROCESS,
};

typedef struct 		s_arg
{
	size_t			type;
	size_t			oct;
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
	int				name_label;
	enum e_state	state;
	char			*comment;
	t_list			*cur_label;
	t_list			*label_list;
}					t_stack;














