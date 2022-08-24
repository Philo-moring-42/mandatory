/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:18:50 by hogkim            #+#    #+#             */
/*   Updated: 2022/08/24 17:18:51 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_rule	rule;

	if (!parsing(argc, argv, &rule))
	{
		printf("FAIL\n");
		return (0);
	}
	philo_run(&rule);
	return (0);
}
