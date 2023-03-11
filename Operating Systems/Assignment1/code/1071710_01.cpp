#include <stdio.h> //ok
#include <stdlib.h>//ok
#include <unistd.h>//ok
#include <fcntl.h> // for O_constants
#include <sys/mman.h>
#include <sys/wait.h>
void error_and_die(const char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}
int collatz(int n){
	if(n==1)
	{
		return 1;
	}
	if(n%2==0)//even
	{
		return n/2;
	}
	else if(n%2!=0)//odd
	{
		return 3*n+1;
	}
	return 0;
}

int main()
{
	pid_t pid;
	int n=0;
	//input 1-100 n complete 1
	while(1){
		scanf("%d",&n); 
		if(n>=1 && n<=100){
			break;
		}
	};
	// open shared memory
	int fd = shm_open("myregion",O_CREAT|O_RDWR,0666);
	if(fd==-1)// handle error
		error_and_die("shm_open"); 
	if(ftruncate(fd,5*sizeof(int)) != 0) // handle error
		error_and_die("ftruncate");
	int *ptr=(int*)mmap(NULL, 5*sizeof(int), PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);//0 is a pid position , 1 is a collatz, 2 is a max, 3 is a order, 4 is a count
	if(ptr == MAP_FAILED)
		error_and_die("mmap");
	close(fd); 
	// make child process
	pid = fork(); // complete 2	
	if (pid>0) // parent process
	{
		//pid will get child process id
		ptr[0] = pid;
		ptr[1] = n;
		ptr[2] = 0;
		ptr[3] = 0;
		ptr[4] = 0;
		while(true){
			if(ptr[0] == getpid()){
				ptr[1] = collatz(ptr[1]);
				ptr[4] = ptr[4]+1;
				printf("[%d Parent]:%d\n",ptr[0],ptr[1]);
				if(ptr[1]>ptr[2])
				{	
					ptr[2]=ptr[1];
					ptr[3]=ptr[4];
				}
				ptr[0] = pid;
				if(ptr[1] == 1)
				{	
				ptr[1] = 0;
				break;
				}
			}

		}
		wait(NULL);
	}
	else if(pid == 0) //child process
	{	
		while(true){
			if(ptr[1]==0)
			{
				ptr[0] = getppid();
				break;
			}
			if(ptr[0] == getpid()){
				ptr[1] = collatz(ptr[1]);
				ptr[4] = ptr[4]+1;
				printf("[%d Child]:%d\n",ptr[0],ptr[1]);
				if(ptr[1]>ptr[2])
				{
					ptr[2]=ptr[1];
					ptr[3]=ptr[4];
				}
				ptr[0] = getppid();
			}
		}
		exit(0);
	}
	else{
		printf("error");
		exit(0);
	}
	
	printf("Max:%d\n",ptr[2]);
	printf("Order:%d\n",ptr[3]);
	return 0;
};

