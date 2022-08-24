/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:18:09 by hogkim            #+#    #+#             */
/*   Updated: 2022/08/24 17:18:13 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	print_terminal(t_param *param, int tid, char *str)
{
	pthread_mutex_lock(&param->is_dining_lock);
	if (param->rule->is_dining == TRUE)
	{
		pthread_mutex_lock(&param->print_lock);
		printf("[%lld] %d %s\n", get_time(param) - param->start_time, tid, str);
		pthread_mutex_unlock(&param->print_lock);
	}
	pthread_mutex_unlock(&param->is_dining_lock);
}
