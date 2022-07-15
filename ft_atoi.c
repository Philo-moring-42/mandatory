/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:33:37 by surlee            #+#    #+#             */
/*   Updated: 2022/07/15 10:29:34 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	if (str[i] == '+')
		++i;
	/*i = (*str == '+' || *str == '-')
	sign = 1 - ((str[i] == '-') << 1);
	이렇게 두 줄로 줄일 수도 있음!*/
	result = 0;
	while (ft_is_digit(str[i]))
		result = result * 10 + (str[i++] - '0');
	if (result < -2147483648 || result > 2147483647)
		return (FAIL);
	return ((int)(result));
}
