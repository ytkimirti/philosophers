/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:40:15 by ykimirti          #+#    #+#             */
/*   Updated: 2022/08/19 14:40:20 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H

# define UTILS_H

# include <time.h>

# include "vars.h"

int		ft_atoi(const char *nptr);
int		ft_isspace(char c);
t_time	get_time(void);

#endif
