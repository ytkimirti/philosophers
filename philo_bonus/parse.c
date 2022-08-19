/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:32:03 by ykimirti          #+#    #+#             */
/*   Updated: 2022/08/19 10:33:40 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "vars.h"
#include "errors.h"
#include "utils.h"

void	check_values(t_vars *vars)
{
	if (vars->count > SEM_VALUE_MAX)
		exit_program("You can have at most SEM_VALUE_MAX forks!");
	if (vars->count < 2
		|| vars->starve_time < 0 || vars->eat_time < 0
		|| vars->sleep_time < 0)
		exit_program("All values should be positive and "
			"There must be at least 2 philosophers.");
}

// Args are: 
// number_of_philosophers
// time_to_die
// time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]
void	parse_args(t_vars *vars, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		exit_program("Argument count does not match\n"
			"./philo time_to_die time_to_eat "
			"time_to_sleep [must_eat_count]");
	vars->count = ft_atoi(argv[1]);
	vars->starve_time = ft_atoi(argv[2]);
	vars->eat_time = ft_atoi(argv[3]);
	vars->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
	{
		vars->is_infinite = false;
		vars->max_eat_count = ft_atoi(argv[5]);
	}
	else
	{
		vars->is_infinite = true;
		vars->max_eat_count = 0;
	}
	check_values(vars);
}
