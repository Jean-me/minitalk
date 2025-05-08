/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesasaki <mesasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:09:49 by mesasaki          #+#    #+#             */
/*   Updated: 2025/05/08 20:41:58 by mesasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _GNU_SOURCE
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include "ft_printf/ft_printf.h"

typedef struct s_state
{
	int		bit;
	char	c;
}			t_state;

void	handle_signal(int signum, siginfo_t *info, void *context);
void	ack_handler(int signum);
void	send_bit(pid_t pid, int bit);
void	send_char(pid_t pid, char c);
void	send_string(pid_t pid, const char *str);
#endif