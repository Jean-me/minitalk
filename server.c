#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_state
{
	int		bit;
	char	c;
}			t_state;

void	handle_signal(int signum, siginfo_t *info, void *context)
// state.bitが8になるまで9かい繰り返し
{
	static t_state state;
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
	pid_t client_pid = info->si_pid;
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction sa;

	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;

	printf("受信プロセス PID: %d\n", getpid());

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	while (1)
		pause();
	return (0);
}