/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesasaki <mesasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:06:18 by mesasaki          #+#    #+#             */
/*   Updated: 2025/05/08 21:18:16 by mesasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "ft_printf/ft_printf.h"

t_state	state;

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	pid_t			client_pid;

	(void)context;
	if (signum == SIGUSR2)
		state.c |= (1 << (7 - state.bit));
	state.bit++;
	if (state.bit == 8)
	{
		if (state.c == '\0')
			write(1, "\n", 1);
		else
			write(1, &state.c, 1);
		state.bit = 0;
		state.c = 0;
	}
	client_pid = info->si_pid;
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	ft_printf("受信プロセス PID: %d\n", getpid());
	if(sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
		return (1);
	while (1)
		pause();
	return (0);
}
