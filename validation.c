/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c     		                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 19:10:54 by namina             #+#    #+#            */
/*   Updated: 2021/09/10 19:10:54 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>
# include "readline/include/readline/readline.h"
# include "readline/include/readline/history.h"
# include "readline/include/readline/rltypedefs.h"
# include "libft/libft.h"

#define PIPE 1
#define REDRCT_OUTPUT 2
#define REDRCT_APPEND 3
#define REDRCT_INPUT 4
#define HERE_DOC 5

typedef struct s_list_params
{
	char	**cmd_arr;
	char	*str_to_cmd;
	char	*path_app;
	int		fd[2];
	char	*here_doc_limiter;
	int		input_mod;
	int 	output_mode;
	char 	*input_file;
	char 	*output_file;
}			t_list_params;

/* TODO
 * check program (stat?)
 * check redirects
 *
 * */

int	check_exe_rights(char *file_name)
{
	struct stat buf;
	int			exe_right;

	stat(file_name, &buf);
	exe_right = ((buf.st_mode >> 6) & 0001) == 0001;
	return (exe_right);
}

int	validation(t_list *param_list)
{

	printf("buf: %i", check_exe_rights(((t_list_params *)param_list->content)->input_file) );
	return (0);
}
