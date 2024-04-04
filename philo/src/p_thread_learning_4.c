#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 23, 29 };

void	*routine(void *arg)
{
	int	j;
	int	sum;
	int	index;

	j = 0;
	sum = 0;
	index = *(int *)arg;
	while (j < 5)
	{
		sum =+ primes[index + j];
		j++;
	}
	
}

int main(void)
{
	int	i;
	int *a;
	int	*res;
	pthread_t th[2];

	i = 0;
	while (i < 2)
	{
		a = malloc(sizeof(int));
		*a = i * 5;
		pthread_create(&th[i], NULL, &routine, a);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		pthread_join(th[i], (void **)&res);
		i++;
	}
	printf("The sum of the first ten prime numbers are %d: \n", *res);
	free(res);
}
