/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:39:22 by ykimirti          #+#    #+#             */
/*   Updated: 2022/08/19 14:39:24 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H

# define INIT_H

# include "vars.h"

void	init_philosophers(t_vars *vars);
int		*init_processes(t_vars *vars);

#endif
