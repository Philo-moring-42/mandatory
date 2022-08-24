/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:40:57 by hjeong            #+#    #+#             */
/*   Updated: 2022/08/24 16:49:32 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

static void	free_all(t_param *param)
{
	free(param->forks);
	free(param->philo);
	free(param->tids);
}

static void	detach_pthreads(int i, t_param *param)
{
	int	index;

	index = 0;
	while (index < i)
	{
		pthread_detach(param->tids[index]);
		++index;
	}
	free_all(param);
}

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
	if (tid % 2 == 1)
	{
		pthread_mutex_lock(&philo->param->starving_time_lock);
		philo->start_starving_time = get_time(philo->param);
		pthread_mutex_unlock(&philo->param->starving_time_lock);
		usleep(philo->param->rule->time_to_eat * 800);
	}
	pthread_mutex_lock(&philo->param->is_dining_lock);
	while (philo->param->rule->is_dining == TRUE)
	{
		pthread_mutex_unlock(&philo->param->is_dining_lock);
		dining_philo_eat(philo, tid);
		philo_sleep(philo->param->rule, philo, philo->tid_index);
		philo_think(philo->param->rule, philo, philo->tid_index);
		pthread_mutex_lock(&philo->param->is_dining_lock);
	}
	pthread_mutex_unlock(&philo->param->is_dining_lock);
	return (NULL);
}

void	philo_run(t_rule *rule)
{
	int			i;
	t_param		param;

	if (init_param(&param, rule) == FAIL)
		return ;
	i = 0;
	param.start_time = get_time(&param);
	while (i < rule->num_of_philo)
	{
		param.philo[i].tid_index = i;
		if (pthread_create(&param.tids[i], NULL, philo_act, &param.philo[i]))
		{
			detach_pthreads(i, &param);
			return ;
		}
		++i;
	}
	if (monitoring_philos(&param) == KILL_PROCESS && rule->num_of_philo != 1)
	{
		i = 0;
		while (i < rule->num_of_philo)
			pthread_join(param.tids[i++], NULL);
	}
	free_all(&param);
}
