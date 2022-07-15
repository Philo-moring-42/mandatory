/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:33:37 by surlee            #+#    #+#             */
/*   Updated: 2022/07/15 10:09:41 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	while (ft_is_space(str[i]))
		i++;
	/*is_space가 진짜 필요할까? argv가 애초에 나뉘어 오는데*/
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	/*i = (*str == '+' || *str == '-')
	sign = 1 - ((str[i] == '-') << 1);
	이렇게 두 줄로 줄일 수도 있음!*/
	result = 0;
	while (ft_is_digit(str[i]))
		result = result * 10 + (str[i++] - '0');
	/*반복문 안에 str[i]를 넣고 is_disit은 반복문 안에*/
	return ((int)(sign * result));
}
