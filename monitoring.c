/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeong <hjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:33:15 by hjeong            #+#    #+#             */
/*   Updated: 2022/07/25 11:16:39 by hjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

static int	check_eat_count(t_param *param)
{
	int	i;
	int	num_of_hogs;

	num_of_hogs = 0;
	i = 0;
	while (i < param->rule->num_of_philo)
	{
		if (param->philo[i].eat_count >= param->rule->count_of_must_eat)
			++num_of_hogs;
		++i;
	}
	if (num_of_hogs == param->rule->num_of_philo)
	{
		pthread_mutex_lock(&param->is_dining_lock);
		param->rule->is_dining = FALSE;
		pthread_mutex_unlock(&param->is_dining_lock);
		pthread_mutex_lock(&param->print_lock);
		printf("all philosophers have became hogs\n");
		return (KILL_PROCESS);
	}
	return (KEEP_PROCESS);
}

static int	check_death_of_philo(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->rule->num_of_philo)
	{
		if ((get_time(param) - param->philo[i].start_starving_time \
			> param->rule->time_to_die))
		{
			pthread_mutex_lock(&param->is_dining_lock);
			param->rule->is_dining = FALSE;
			pthread_mutex_unlock(&param->is_dining_lock);
			pthread_mutex_lock(&param->print_lock);
			printf("[%lld] %d %s\n", get_time(param) \
				- param->start_time, i + 1, "died");
			return (KILL_PROCESS);
		}
		++i;
	}
	return (KEEP_PROCESS);
}

int	monitoring_philos(t_param *param)
{
	while (param->num_of_threads < param->rule->num_of_philo)
		usleep(10);
	param->start_time = get_time(param);
	while (1)
	{
		if (check_death_of_philo(param) == KILL_PROCESS)
			break ;
		if (param->rule->if_count_of_must_eat == TRUE && \
			check_eat_count(param) == KILL_PROCESS)
			break ;
	}
	return (KILL_PROCESS);
}
