#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

int main()
{
	sem_t *seme = sem_open("name",O_CREAT, 0644, 22);
	int val;
	if (seme == SEM_FAILED)
		return (-1);
	sem_getvalue(seme, &val);
	printf("sem value is %d \n", val);
}