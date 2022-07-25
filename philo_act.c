/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeong <hjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:40:57 by hjeong            #+#    #+#             */
/*   Updated: 2022/07/25 11:13:45 by hjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	dining_philo_eat(t_philo *philo, int tid)
{
	pthread_mutex_lock(philo->left_fork);
	print_terminal(philo->param, tid + 1, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_terminal(philo->param, tid + 1, "has taken a fork");
	philo_eat(philo->param->rule, philo, philo->tid_index);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	*philo_act(void *data)
{
	int		tid;
	t_philo	*philo;

	philo = (t_philo *)data;
	tid = philo->tid_index;
	while (philo->param->num_of_threads < philo->param->rule->num_of_philo)
		usleep(10);
	philo->start_starving_time = get_time(philo->param);
	// if (tid % 2 == 1)
	// 	usleep(philo->param->rule->time_to_eat * 800);
	while (philo->param->rule->is_dining == TRUE)
	{
		dining_philo_eat(philo, tid);
		philo->start_starving_time = get_time(philo->param);
		philo_sleep(philo->param->rule, philo, philo->tid_index);
		philo_think(philo->param->rule, philo, philo->tid_index);
	}
	return (NULL);
}

int	philo_run(t_rule *rule)
{
	int			i;
	t_param		param;

	if (init_param(&param, rule) == FAIL)
		return (FAIL);
	i = 0;
	while (i < rule->num_of_philo)
	{
		param.philo[i].tid_index = i;
		pthread_create(&param.tids[i], NULL, philo_act, &param.philo[i]);
		pthread_mutex_lock(&param.thread_lock);
		++param.num_of_threads;
		pthread_mutex_unlock(&param.thread_lock);
		++i;
	}
	if (monitoring_philos(&param) == KILL_PROCESS && rule->num_of_philo != 1)
	{
		i = 0;
		while (i < rule->num_of_philo)
		{
			pthread_join(param.tids[i], NULL);
			++i;
		}
	}
	return (SUCCESS);
}
