/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:15:15 by ykimirti          #+#    #+#             */
/*   Updated: 2022/09/14 18:15:50 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H

# define INIT_H

# include "vars.h"

bool	init_philosophers(t_vars *vars);
bool	init_mutexes(t_vars *vars);
bool	init_threads(t_vars *vars);
void	destroy_mutexes(t_vars *vars);
void	join_threads(t_vars *vars);

#endif
