#ifndef INIT_H

# define INIT_H

# include "vars.h"

bool	init_philosophers(t_vars *vars);
bool	init_semaphores(t_vars *vars);
bool	init_processes(t_vars *vars);
void	destroy_semaphores(t_vars *vars);
void	join_processes(t_vars *vars);

#endif
