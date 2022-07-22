/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjeong <hjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:32:47 by hjeong            #+#    #+#             */
/*   Updated: 2022/07/22 16:32:44 by hjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

long long	get_time(t_param *param)
{
	struct timeval	time;
	long long		ms;

	pthread_mutex_lock(&param->get_time_lock);
	gettimeofday(&time, NULL);
	pthread_mutex_unlock(&param->get_time_lock);
	ms = (time.tv_sec) * 1000 + (time.tv_usec) / 1000;
	return (ms);
}
