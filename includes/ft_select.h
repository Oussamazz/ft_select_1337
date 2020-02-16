/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 09:25:06 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/16 03:12:27 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdlib.h>
# include <stdbool.h>
# include <termcap.h>
# include "libft.h"
# include <stdio.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <sys/stat.h>
# include <ftw.h>
# include <unistd.h>
# include <sys/param.h>
# define NO_ZERO(X) ((X) == 0 ? (X) = 1 : (X))

# define T_C_COLOR				"\033[35m"
# define T_DIR_COLOR			"\033[1;36m"
# define T_O_COLOR				"\033[32m"
# define T_H_COLOR				"\033[35m"
# define T_MAKEFILE_COLOR		"\033[33m"
# define T_DOT_COLOR			"\033[32m"
# define T_A_COLOR				"\033[32m"
# define DEFAULT_COLOR			"\033[0m"
# define REVERSE_VIDEO_COLOR	"\033[7m"
# define RESET_COLOR			"\033[0m"
# define BOLD_COLOR				"\033[1m"
# define INTENSTY				"\033[0;100m"
# define UNDERLINED				"\033[4m"

# define Y_KEY					121
# define N_KEY					110
# define ENTER_KEY				10
# define ESC_KEY				27
# define SPACE_KEY				32
# define OPEN_KEY				111
# define BACK_KEY				98
# define BSP_KEY				127
# define DEL_KEY				2117294875
# define LEFT_KEY				4479771
# define UP_KEY					4283163
# define RIGHT_KEY				4414235
# define DOWN_KEY				4348699
# define STAR_KEY				42
# define DLT_ALL_KEY			45

typedef enum		e_type
{
	C_FILE,
	O_FILE,
	H_FILE,
	A_FILE,
	MAKE_FILE,
	DOT_FILE,
	DIR_FILE,
	UNK_FILE,
}					t_type;

typedef enum		e_direction
{
	UP_dir,
	RIGHT_dir,
	DOWN_dir,
	LEFT_dir,
	UNK_dir,
}					t_direction;

typedef	struct		s_args
{
	int				index;
	char			*value;
	bool			is_on;
	t_type			type;
	struct 	s_args 	*next;
	struct 	s_args	*prev;
}					t_args;

typedef	struct	s_select
{
	t_args			*args;
	t_args			**active_arg;
	int				colomns;
	int				rows;
	int				glb_fd;
	int				argc;
	bool			real_mode;
	char			*term_value;
	unsigned int	selected_counter;
	struct	termios old_attribute;
	struct	termios	attribute;
}				t_select;

t_select	g_HEAD;

/*
** DLL functions
*/
void	ft_push_ddl(char *value, int index);
void	delete_item(void);
/*
** Printing Functions
*/
void	ft_show(void);
void    ft_select_loop(void);
int    	ft_putchar_term(int c);
void	print_selected_items(void);

/*
**Cursor
*/
void	un__select_all(int key);
void	selecting(void);
void    up_(void);
void    down_(void);
/*
** Error Functions
*/
void	error(char *error_type);
void	error_usage(void);
void	env_TERM(void);

/*
** Arguments Manipulation
*/
void    get_args(char **av);
void    check_flag(char *flag);
t_type	get_type(char *data);


/*
** Signals handling
*/
void	init_signal(void);
void    signal_kill(void);
void	signal_handler(int no_sig);
void	suspend(void);

/*
**init / reset terminal function
*/
void	init_terminal(void);
void    reset_terminal(void);
void    free_all(void);

/*
**Counting function
*/
size_t      biggest_len_arg(void);
int			window_size(int width_height);
int			count_colomns(void);

/*
**Browsing
*/
void    browse(void);
void    browse_back(void);

/*
** OTHERS
*/
void		print_list(int rows, int colomns);
int 		check_access(char *path);
# endif
