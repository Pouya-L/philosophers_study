/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plashkar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:28:43 by plashkar          #+#    #+#             */
/*   Updated: 2023/12/14 15:48:22 by plashkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"


void	eat(void *philo_id)
{
	printf("The Pilosopher number %ld is shitting\n", (size_t)philo_id);

	//stimulate shitting
	sleep(2);

	printf("The philosopher number %ld stopped shitting\n", (size_t)philo_id);
}
void	*philo_shit(void *philo_id)
{
	sem_wait(&bathroom_semaphore);

	eat(philo_id);

	//Send signal and increment the semaphore
	sem_post(&bathroom_semaphore);

	return (NULL);
}

int	main(int argc, char **argv)
{
	size_t	number_of_philosophers;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	i;

	if (argc != 2)
	{
		printf("Invalid numebr of arguments");
		return (1);
	}
	number_of_philosophers = atol(argv[1]);
	(void)time_to_die;
	(void)time_to_eat;
	(void)time_to_sleep;
	sem_init(&bathroom_semaphore, 0, 1);

	i = 0;
	pthread_t philo[number_of_philosophers];
	while (i < number_of_philosophers)
	{
		pthread_create(&philo[i], NULL, philo_shit, (void *)i);
		i++;
		usleep(500);
	}
	i = 0;
	while(i < number_of_philosophers)
	{
		pthread_join(philo[i], NULL);
		i++;
	}

	sem_destroy(&bathroom_semaphore);

	return (0);
}

