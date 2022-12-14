/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:15:44 by ykimirti          #+#    #+#             */
/*   Updated: 2022/09/14 18:57:09 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# include <time.h>

# include "vars.h"

int		ft_atoi(const char *nptr);
int		ft_isspace(char c);
t_time	get_time(void);
bool	get_stop_mutex(t_vars *vars);
bool	did_philo_starve(t_philo *p, bool use_mutex);

#endif
