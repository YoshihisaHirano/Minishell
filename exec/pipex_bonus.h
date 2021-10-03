/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>         +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 19:10:19 by namina             #+#    #+#            */
/*   Updated: 2021/08/12 19:10:19 by namina            ###    #######.fr      */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdlib.h>

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char			**cmd_arr;
	char			*path_app;
	int				fd[2];
	char			*limiter;
					input -1
					output pipe
					option
					mode
}					t_list;

char	**get_path_arr(char **envp, char *app_name);
char	*get_path(char *absolute_path, char *app_name);
void	parser(t_list **param_list, char **argv, char **input_file,
			   char **output_file);
void	set_path_arr(char **current_path_arr, char *app_name);
int		validation(char *input_file, t_list *param_list, int argc, char **envp);
void	set_child_fd(t_list *params, int input_fd, int last_output_fd);
int		get_next_line(int fd, char **line);
void	get_input_from_std(char *limiter, int fd);
int		error_handle_program(char *app_name);
int		error_handle_argc(void);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(char *src);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(char **cmd_arr);
void	ft_lstclear(t_list **lst);
void	free_array(char **arr);
#endif
