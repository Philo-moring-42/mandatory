/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:19:07 by hogkim            #+#    #+#             */
/*   Updated: 2022/08/24 17:19:08 by hogkim           ###   ########.fr       */
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
