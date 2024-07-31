#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
 #include <sys/types.h>
#include	<sys/wait.h>

int main()
{
	// sem_t *seme = sem_open("name",O_CREAT, 0644, 22);
	// if (seme == SEM_FAILED)
	// 	return (-1);


	int pid, status;

	pid = fork();

	if (pid == 0)
	{

		sleep(3);
		exit(25);
	}
	else
	{
		waitpid(-1, &status, 0);
		printf("pid is %d \n",WEXITSTATUS(status));
	}
	// if (sem_unlink("name"))
	// {
	// 	printf("erdsfrn o is %d \n", errno);
	// 	perror("");
	// 	exit(20);
	// }
	// if (sem_close(seme))
	// {
	// 	printf("errno is %d \n", errno);
	// 	perror("");
	// 	exit(20);
	// }
	// if (sem_close(seme))
	// {
	// 	printf("errno is %d \n", errno);
	// 	perror("");
	// 	exit(20);
	// }
	// if (sem_unlink("name"))
	// {
	// 	printf("erdsfrn o is %d \n", errno);
	// 	perror("");
	// 	exit(20);
	// }
	// if (sem_close(seme))
	// {
	// 	printf("errno is %d \n", errno);
	// 	perror("");
	// 	exit(20);
	// }
	// if (sem_close(seme))
	// {
	// 	perror("");
	// 	exit(20);
	// }
	// int val = 55;
	// sem_getvalue(seme, &val);
	// printf("sem value is %d \n", val);
}