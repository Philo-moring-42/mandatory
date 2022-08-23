/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:32:49 by hjeong            #+#    #+#             */
/*   Updated: 2022/08/23 20:49:59 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	destroy_mutex(int i, t_param *param, int rule_num)
{
	int	start;

	if (rule_num >= 1)
		pthread_mutex_destroy(&param->print_lock);
	if (rule_num >= 2)
		pthread_mutex_destroy(&param->is_dining_lock);
	if (rule_num >= 3)
		pthread_mutex_destroy(&param->get_time_lock);
	if (rule_num >= 4)
	{
		pthread_mutex_destroy(&param->starving_time_lock);
		start = 0;
		while (start < i)
		{
			pthread_mutex_destroy(&param->forks[start]);
			++start;
		}
	}
}

static int	init_mutex_forks(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->rule->num_of_philo)
	{
		if (pthread_mutex_init(&param->forks[i], NULL))
		{
			destroy_mutex(i, param, 4);
			return (FAIL);
		}
		++i;
	}
	return (SUCCESS);
}

static int	init_philo(t_param *param)
{
	int	i;

	param->philo = malloc(sizeof(t_philo) * param->rule->num_of_philo);
	if (!param->philo)
		return (FAIL);
	i = 0;
	while (i < param->rule->num_of_philo)
	{
		param->philo[i].param = param;
		param->philo[i].eat_count = 0;
		param->philo[i].start_starving_time = get_time(param);
		param->philo[i].left_fork = &param->forks[i];
		param->philo[i].right_fork = &param->forks[(i + 1) \
			% param->rule->num_of_philo];
		++i;
	}
	return (SUCCESS);
}

static int	init_mutex(t_param *param)
{
	if (pthread_mutex_init(&param->print_lock, NULL))
		return (FAIL);
	if (pthread_mutex_init(&param->is_dining_lock, NULL))
	{
		destroy_mutex(0, param, 1);
		return (FAIL);
	}
	if (pthread_mutex_init(&param->get_time_lock, NULL))
	{
		destroy_mutex(0, param, 2);
		return (FAIL);
	}
	if (pthread_mutex_init(&param->starving_time_lock, NULL))
	{
		destroy_mutex(0, param, 3);
		return (FAIL);
	}
	if (init_mutex_forks(param) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	init_param(t_param *param, t_rule *rule)
{
	param->rule = rule;
	param->forks = malloc(sizeof(pthread_mutex_t) * rule->num_of_philo);
	if (!param->forks)
		return (FAIL);
	param->tids = malloc(sizeof(pthread_t) * rule->num_of_philo);
	if (!param->tids)
	{
		free(param->forks);
		return (FAIL);
	}
	if (init_mutex(param) == FAIL)
	{
		free(param->forks);
		free(param->tids);
		return (FAIL);
	}
	if (init_philo(param) == FAIL)
	{
		destroy_mutex(param->rule->num_of_philo, param, 4);
		free(param->forks);
		free(param->tids);
		return (FAIL);
	}
	return (SUCCESS);
}
