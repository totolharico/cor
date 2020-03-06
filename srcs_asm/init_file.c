#include "../includes/asm.h"
#include "../libft/includes/libft.h"


static int		start_file(t_cor_file *out_file, char *source_file, int i)
{
	out_file->total_size = 0;
	out_file->prog_size = 0;
	out_file->name = ft_memalloc(i + 4);
	out_file->content = ft_memalloc(MAX_SIZE_FILE);
	out_file->name = ft_memcpy(out_file->name, source_file, i + 1); 
	out_file->name = ft_stricat(out_file->name, "cor", i + 1); 
	out_file->fd = open(out_file->name, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (out_file->fd <= 0)
	{
		asm_erno("0", SOURCE_FILE_ERR);
		return (FALSE);
	}
	return (TRUE);
}

int		init_file(t_cor_file *out_file, char *source_file)
{
	int		i;

	i = 0;
	while (source_file[i] && source_file[i] != '.')
			i++;
	if (source_file[i] == '\0' || source_file[i + 1] == '\0' || source_file[i + 1] != 's' || source_file[i + 2] != '\0')
	{
		asm_erno("0", SOURCE_FILE_ERR);
		return (FALSE);
	}
	if (start_file(out_file, source_file, i) == FALSE)
		return (FALSE);
	return (TRUE);
}