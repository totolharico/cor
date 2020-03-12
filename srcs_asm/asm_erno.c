#include "../includes/asm.h"
#include "../libft/includes/libft.h"

void	asm_erno(char *line, uint32_t error)
{
	char	*output;

	if (line == NULL)
		output = "MALLOC ERROR";
	else if (error & BAD_COMMENT)
		output = ft_strjoin("BAD COMMENT, line: ", line);
	else if (error & NAME_ERR)
		output = ft_strjoin("NAME ERROR, line: ", line);
	else if (error & MISSING_QUOTE)
		output = "MISSING QUOTE";
	else if (error & COMMENT_ERR)
		output = ft_strjoin("COMMENT ERROR, line: ", line);
	else if (error & OP_ERR)
		output = ft_strjoin("OP ERROR, line: ", line);
	else if (error & ARG_ERR)
		output = ft_strjoin("ARG ERROR, line: ", line);
	else if (error & TAG_ERR)
		output = ft_strjoin("TAG ERROR, line: ", line);
	else if (error & READ_ERR)
		output = "READ ERROR";
	else if (error & MALLOC_ERR)
		output = ft_strjoin("MALLOC ERROR, line: ", line);
	else if (error & NAME_ERR)
		output = "FILE ERROR";
	else if (error & SOURCE_FILE_ERR)
		output = "SOURCE FILE ERROR";
	else if (error & LABEL_CALL_ERR)
		output = "LABEL_CALL_ERROR";
	if (output == NULL)
		output = "MALLOC ERROR";
	ft_putendl_fd(output, 2);
}