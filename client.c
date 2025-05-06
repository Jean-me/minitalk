#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		g_ack_received;

void	ack_handler(int signum)
{
	if (signum == SIGUSR1)
		write(1, ".", 1);
	g_ack_received = 1;
}

void	send_bit(pid_t pid, int bit)
{
	g_ack_received = 0;
	if (bit == SIGUSR2)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
	while (!g_ack_received)
		usleep(100);
	g_ack_received = 0;
	// pause(); // ACKまち
}

void	send_char(pid_t pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			send_bit(pid, SIGUSR2);
		// kill(pid, SIGUSR2);
		else
			send_bit(pid, SIGUSR1);
		// kill(pid, SIGUSR1);
		// while (!g_ack_received)
		// 	usleep(100);
		// g_ack_received = 0;
		i--;
	}
}

void	send_string(pid_t pid, const char *str)
{
	while (*str)
	{
		send_char(pid, *str);
		str++;
	}
	send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	pid_t server_pid;
	struct sigaction sa;

	if (argc != 3)
	{
		printf("使い方: %s [受信者のPID] [送る文字列]\n", argv[0]);
		return (1);
	}
	sa.sa_handler = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	server_pid = (pid_t)atoi(argv[1]); //手動で入れた受信者のPID
	send_string(server_pid, argv[2]);  //文字をサーバーPIDを指定して送る

	return (0);
}