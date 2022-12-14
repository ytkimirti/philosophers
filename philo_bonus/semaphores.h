/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:40:10 by ykimirti          #+#    #+#             */
/*   Updated: 2022/09/12 11:40:09 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEMAPHORES_H

# define SEMAPHORES_H

# include "vars.h"

# define SEM_FORKS "/phil_forks"
# define SEM_CLOSING "/phil_closing"
# define SEM_WRITING "/phil_writing"

# define SEM_STATE_READ "/phil_state_read"

void	init_semaphores(t_vars *vars);
void	close_semaphores(t_vars *vars);
sem_t	*open_semaphore(char *name, int initial);
sem_t	*open_semaphore_with_id(char *prefix, int id, int initial);
void	close_semaphore(sem_t *sem, const char *name);

#endif
