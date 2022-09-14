/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykimirti <ykimirti@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:13:50 by ykimirti          #+#    #+#             */
/*   Updated: 2022/09/14 18:13:50 by ykimirti         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "colors.h"
#include <stdbool.h>

bool	exit_program(char *message)
{
	if (message == NULL)
		printf("Error\n");
	else
		printf("Error: %s\n", message);
	return (false);
}
