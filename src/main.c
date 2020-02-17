/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 13:28:25 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/17 14:33:30 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			entry_init(char *tty_name)
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

void			sig_continue(void)
{
	signal(SIGIOT, signal_handler);
	signal(SIGEMT, signal_handler);
	signal(SIGBUS, signal_handler);
	signal(SIGSYS, signal_handler);
	signal(SIGURG, signal_handler);
	signal(SIGIO, signal_handler);
	signal(SIGXCPU, signal_handler);
	signal(SIGXFSZ, signal_handler);
	signal(SIGVTALRM, signal_handler);
	signal(SIGINFO, signal_handler);
	signal(SIGPROF, signal_handler);
	signal(SIGCHLD, SIG_IGN);
}

void			init_signal(void)
{
	signal(SIGWINCH, signal_handler);
	signal(SIGABRT, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGSTOP, signal_handler);
	signal(SIGCONT, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGKILL, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGHUP, signal_handler);
	signal(SIGILL, signal_handler);
	signal(SIGFPE, signal_handler);
	signal(SIGSEGV, signal_handler);
	signal(SIGPIPE, signal_handler);
	signal(SIGALRM, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	signal(SIGTTIN, signal_handler);
	signal(SIGTTOU, signal_handler);
	signal(SIGTRAP, signal_handler);
	sig_continue();
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
	init_terminal();
	init_signal();
	if (av[1][0] == '-' && av[1][1] != '\0')
		check_flag(av[1]);
	if (av[1][0] == '-')
		get_args(av + 2);
	else
		get_args(av + 1);
	ft_select_loop();
	reset_terminal();
	print_selected_items();
	free_all();
	close(g_HEAD.glb_fd);
	return (0);
}
