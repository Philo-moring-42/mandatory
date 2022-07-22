/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeong <hjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:53:10 by hjeong            #+#    #+#             */
/*   Updated: 2022/07/22 17:05:08 by hjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	spending_time(t_param *param, long long time_to_spend)
{
	long long	target_time;

	target_time = get_time(param) + time_to_spend;
	while (get_time(param) < target_time)
		usleep(100);
}

void	philo_eat(t_rule *rule, t_philo *philo, int tid)
{
	if (rule->is_dining == FALSE)
		return ;
	print_terminal(philo->param, tid + 1, "is eating");
	spending_time(philo->param, rule->time_to_eat);
	++(philo->eat_count);
}

void	philo_sleep(t_rule *rule, t_philo *philo, int tid)
{
	if (rule->is_dining == FALSE)
		return ;
	print_terminal(philo->param, tid + 1, "is sleeping");
	spending_time(philo->param, rule->time_to_sleep);
}

void	philo_think(t_rule *rule, t_philo *philo, int tid)
{
	if (rule->is_dining == FALSE)
		return ;
	print_terminal(philo->param, tid + 1, "is thinking");
	usleep(50);
}
