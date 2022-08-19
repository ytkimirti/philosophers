/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:39:47 by ykimirti          #+#    #+#             */
/*   Updated: 2022/08/19 14:40:03 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "semaphores.h"
#include <semaphore.h>
#include "errors.h"
#include <stdio.h>
#include <sys/errno.h>

#define SEM_FORKS "/phil_forks"
#define SEM_CLOSING "/phil_closing"
#define SEM_WRITING "/phil_writing"

// Give the read write execute permissions
// to the semaphore, so:
// -rwx------
sem_t	*open_semaphore(char *name, int initial)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT, S_IRWXU, initial);
	if (sem == SEM_FAILED)
		exit_program("Creating semaphore failed!");
	return (sem);
}

void	init_semaphores(t_vars *vars)
{
	vars->sem_forks = open_semaphore(SEM_FORKS, vars->count);
	vars->sem_closing = open_semaphore(SEM_CLOSING, 0);
	vars->sem_writing = open_semaphore(SEM_WRITING, 1);
}

void	close_semaphore(sem_t *sem, const char *name)
{
	if (sem_close(sem) == -1)
		exit_program("Closing semaphore failed on close");
	if (sem_unlink(name) == -1)
		exit_program("Unlinking semaphore failed on close");
}

void	close_semaphores(t_vars *vars)
{
	close_semaphore(vars->sem_forks, SEM_FORKS);
	close_semaphore(vars->sem_closing, SEM_CLOSING);
	close_semaphore(vars->sem_writing, SEM_WRITING);
}
