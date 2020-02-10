/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:28:25 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/10 06:55:10 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		entry_init(char *tty_name)
{
	int		ret;
	char	entry[1024];

	if (!isatty(g_HEAD.glb_fd))
	{
		ft_putendl_fd("Error: file descriptor is not valid.", 2);
		exit(EXIT_FAILURE);
	}
	if ((ret = tgetent(entry, tty_name)) < 1)
	{
		if (ret == -1)
			ft_putendl_fd("Error: no such entry.", 2);
		else if (ret == 0)
			ft_putendl_fd("Error: terminfo database could not be found.", 2);
		exit(EXIT_FAILURE);
	}
	return ;
}

void		init_signal(void)
{
	signal(SIGWINCH, signal_handler);
	signal(SIGABRT, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGSTOP, signal_handler);
	signal(SIGCONT, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGKILL, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void			init_terminal(void)
{
	if (!(g_HEAD.term_value = getenv("TERM")))
		return (error("TERM"));
	if ((g_HEAD.glb_fd = open("/dev/tty", O_RDWR)) == -1)
		return (error("fd"));
	entry_init(g_HEAD.term_value);
	tcgetattr(g_HEAD.glb_fd, &g_HEAD.old_attribute);
	tcgetattr(g_HEAD.glb_fd, &g_HEAD.attribute);
	g_HEAD.attribute.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(g_HEAD.glb_fd, 0, &g_HEAD.attribute);
	tputs(tgetstr("ti", NULL), 1, ft_putchar_term);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_term);
}

int				main(int ac, char **av, char **env)
{
	if (ac < 2 || (ac == 2 && av[1][0] == '-'))
		error("args");
	ft_memset(&g_HEAD, 0, sizeof(t_select));
	if (av[1][0] == '-' && av[1][1] != '\0')
		check_flag(av[1]);
	init_terminal();
	init_signal();
	get_args(av[1][0] == '-' ? av = av + 2 : av + 1);
	ft_select_loop();
	reset_terminal();
	ft_strdel(&g_HEAD.term_value);
	free_all();
	close(g_HEAD.glb_fd);
	return (0);
}
