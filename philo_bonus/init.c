/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:39:18 by ykimirti          #+#    #+#             */
/*   Updated: 2022/08/19 14:39:18 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "init.h"
#include "philo.h"
#include "vars.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include "colors.h"
#include "utils.h"

void	init_philosophers(t_vars *vars)
{
	int		i;

	vars->philos = (t_philo *)malloc(sizeof(t_philo) * vars->count);
	if (!vars->philos)
		exit_program("malloc on philosopher objects failed!");
	i = 0;
	while (i < vars->count)
	{
		vars->philos[i].id = i + 1;
		vars->philos[i].vars = vars;
		i++;
	}
}


int	*init_processes(t_vars *vars)
{
	int		i;
	int		pid;
	int		*pids;

	pids = (int *)malloc(sizeof(int) * vars->count);
	i = 0;
	vars->stop = false;
	while (i < vars->count)
	{
		pid = fork();
		if (pid == -1)
			exit_program("Forking process failed");
		else if (pid == 0)
			philo_entry(&vars->philos[i]);
		pids[i] = pid;
		i++;
	}
	return (pids);
}
