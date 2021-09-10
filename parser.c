# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include "readline/include/readline/readline.h"
# include "readline/include/readline/history.h"
# include "readline/include/readline/rltypedefs.h"
# include "libft/libft.h"


typedef struct s_list_exe
{
	struct s_list_exe	*next;
	struct s_list_exe	*prev;
	char				**cmd_arr;
	char				*path_app;
	int					fd[2];
	char				*limiter_here_doc;
	char 				output_mod;
	char				input_mod; // if < or <<
}						t_list_exe;


int	set_params_element(char *s_start, char *s_end, t_list_exe *param_list)
{
	int			len_cmd;
	char		*str_cmd;

	len_cmd = s_end - s_start;
	if (!len_cmd)
		return (0);
	str_cmd = malloc(len_cmd);
	ft_strlcpy(str_cmd, s_start, len_cmd);
	param_list->cmd_arr = ft_split(str_cmd, ' ');
	param_list->output_mod = *s_end;
	free(str_cmd);
	return (len_cmd);
}

int main(void)
{
	t_list_exe	param_list;
	char		*s_pointer;
	char		*s_prev_start;
	char 		*input_file;
	char 		*output_file;


	char *s = "echo -n sometext";
	s_pointer = s;
	s_prev_start = s;
	while (*s_pointer)
	{
		if (*s_pointer == '|' || *s_pointer == '>')
		{
			set_params_element(s_prev_start, s_pointer, &param_list);
			s_prev_start = s_pointer;
		}
		s_pointer++;
	}
	if (s_pointer - s_prev_start)
		set_params_element(s_prev_start, s_pointer, &param_list);




	while (*param_list.cmd_arr)
	{
		printf("cmd %s\n", *param_list.cmd_arr);
		param_list.cmd_arr++;
	}
	printf("output mode: %c\n", param_list.output_mod);
	return (0);
}