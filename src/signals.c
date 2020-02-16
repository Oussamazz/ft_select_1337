/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 17:15:41 by oelazzou          #+#    #+#             */
/*   Updated: 2020/02/16 21:56:29 by oelazzou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	reset_terminal(void)
{
	tcsetattr(g_HEAD.glb_fd, TCSANOW, &g_HEAD.old_attribute);
	tputs(tgetstr("te", NULL), 1, ft_putchar_term);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_term);
}

void	suspend(void)
{
	reset_terminal();
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
}

void    signal_kill(void)
{
	reset_terminal();
	free_all();
	exit(EXIT_SUCCESS);
}

void	signal_handler(int no_sig)
{
	if (no_sig == SIGINT || no_sig == SIGABRT || no_sig == SIGSTOP
		|| no_sig == SIGKILL || no_sig == SIGQUIT
		|| no_sig == SIGHUP || no_sig == SIGILL || no_sig == SIGFPE ||
		no_sig == SIGSEGV || no_sig == SIGPIPE || no_sig == SIGALRM ||
		no_sig == SIGTERM || no_sig == SIGUSR1 || no_sig == SIGUSR2 ||
		no_sig == SIGTTIN || no_sig == SIGTTOU || no_sig == SIGTRAP
		|| no_sig == SIGIOT || no_sig == SIGEMT || no_sig == SIGBUS || 
		no_sig == SIGSYS || no_sig == SIGURG || no_sig == SIGIO || 
		no_sig == SIGXCPU || no_sig == SIGXFSZ || no_sig == SIGVTALRM ||
		no_sig == SIGPROF || no_sig == SIGINFO)
		signal_kill();
	else if (no_sig == SIGCONT)
	{
		init_terminal();
		init_signal();
		ft_show();
	}
	else if (no_sig == SIGTSTP)
		suspend();
	else if (no_sig == SIGWINCH || no_sig == SIGCHLD)
		ft_show();
}
