#include<stdlib.h>
#include<stdio.h>
#include<time.h> // about system wall-clock time
#include<iostream> 
#include<pthread.h> // pthread API
#include<unistd.h> // get tid
using namespace std;
pthread_mutex_t chopstick[12]={
PTHREAD_MUTEX_INITIALIZER,
PTHREAD_MUTEX_INITIALIZER,
PTHREAD_MUTEX_INITIALIZER,
PTHREAD_MUTEX_INITIALIZER,
PTHREAD_MUTEX_INITIALIZER,
PTHREAD_MUTEX_INITIALIZER,
PTHREAD_MUTEX_INITIALIZER,
PTHREAD_MUTEX_INITIALIZER,
PTHREAD_MUTEX_INITIALIZER,
PTHREAD_MUTEX_INITIALIZER,
PTHREAD_MUTEX_INITIALIZER,
PTHREAD_MUTEX_INITIALIZER}; // mutex4thread
pthread_mutex_t enter = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t output = PTHREAD_MUTEX_INITIALIZER; 
struct parameter{
	int number;
	int algorithms;
	int total_nums;
};
void *algorithm(void *ptr) {
	parameter *phi; phi = (parameter *)ptr;
	int mode = phi->algorithms; int total = phi->total_nums;int phi_num = phi->number;
	time_t now = time(NULL);
	char time_now[100];
	int eat_time = rand()%(5-1+1)+1; int think_time = rand()%(10-5+1)+5;
	int left = (phi_num%total)+1;int right = phi_num; 
	/*output for first in.*/
	now = time(NULL);
	strftime(time_now,100,"%H:%M:%S",localtime(&now));
	pthread_mutex_lock(&output);
	cout<<time_now<<"-Phi "<<phi_num<<"-Im'in!"<<"\n";
	pthread_mutex_unlock(&output);
	sleep(eat_time);//wait for first eat random wait 1-5 sec.
	switch(mode)
	{
		case 1: //algorithm 1
		for(int i=0;i<10;i++){
			think_time = rand()%(10-5+1)+5; eat_time = rand()%(5-1+1)+1;
			pthread_mutex_lock(&chopstick[left]);//take left chopstick.
			now = time(NULL);
			strftime(time_now,100,"%H:%M:%S",localtime(&now));
			pthread_mutex_lock(&output);
			cout<<time_now<<"-Phi "<<phi_num<<"-taking left chopstick"<<"\n";
			pthread_mutex_unlock(&output);
			pthread_mutex_lock(&chopstick[right]);//take right chopstick.
			now = time(NULL);
			strftime(time_now,100,"%H:%M:%S",localtime(&now));
			pthread_mutex_lock(&output);
			cout<<time_now<<"-Phi "<<phi_num<<"-taking right chopstick"<<"\n";
			pthread_mutex_unlock(&output);
			//get right & left chopstick
			now = time(NULL);
			strftime(time_now,100,"%H:%M:%S",localtime(&now));				
			pthread_mutex_lock(&output);
			cout<<time_now<<"-Phi "<<phi_num<<"-eating"<<"\n";
			pthread_mutex_unlock(&output);
			sleep(eat_time);//eating.... then put down the chopstick.
			now = time(NULL);
			strftime(time_now,100,"%H:%M:%S",localtime(&now));
			pthread_mutex_lock(&output);
			cout<<time_now<<"-Phi "<<phi_num<<"-putting left chopstick"<<"\n";			
			pthread_mutex_unlock(&output);
			pthread_mutex_unlock(&chopstick[left]);
			now = time(NULL);
			strftime(time_now,100,"%H:%M:%S",localtime(&now));
			pthread_mutex_lock(&output);
			cout<<time_now<<"-Phi "<<phi_num<<"-putting right chopstick"<<"\n";
			pthread_mutex_unlock(&output);
			pthread_mutex_unlock(&chopstick[right]);
			now = time(NULL);
			strftime(time_now,100,"%H:%M:%S",localtime(&now));				
			cout<<time_now<<"-Phi "<<phi_num<<"-thinking"<<"\n";
			sleep(think_time);
		}
		break;
		case 2:
		for(int i=0;i<10;i++){
			think_time = rand()%(10-5+1)+5; eat_time = rand()%(5-1+1)+1;
			if(phi_num % 2 != 0){ //odd first pick left then pick right 
				pthread_mutex_lock(&chopstick[left]);//take left chopstick.
				now = time(NULL);
				strftime(time_now,100,"%H:%M:%S",localtime(&now));
				pthread_mutex_lock(&output);
				cout<<time_now<<"-Phi "<<phi_num<<"-taking left chopstick"<<"\n";
				pthread_mutex_unlock(&output);
				pthread_mutex_lock(&chopstick[right]);//take right chopstick.
				now = time(NULL);
				strftime(time_now,100,"%H:%M:%S",localtime(&now));
				pthread_mutex_lock(&output);
				cout<<time_now<<"-Phi "<<phi_num<<"-taking right chopstick"<<"\n";
				pthread_mutex_unlock(&output);
				//get right & left chopstick
				now = time(NULL);
				strftime(time_now,100,"%H:%M:%S",localtime(&now));				
				pthread_mutex_lock(&output);
				cout<<time_now<<"-Phi "<<phi_num<<"-eating"<<"\n";
				pthread_mutex_unlock(&output);
				sleep(eat_time);//eating.... then put down the chopstick.
				now = time(NULL);
				strftime(time_now,100,"%H:%M:%S",localtime(&now));
				pthread_mutex_lock(&output);
				cout<<time_now<<"-Phi "<<phi_num<<"-putting left chopstick"<<"\n";			
				pthread_mutex_unlock(&output);
				pthread_mutex_unlock(&chopstick[left]);
				now = time(NULL);
				strftime(time_now,100,"%H:%M:%S",localtime(&now));
				pthread_mutex_lock(&output);
				cout<<time_now<<"-Phi "<<phi_num<<"-putting right chopstick"<<"\n";
				pthread_mutex_unlock(&output);
				pthread_mutex_unlock(&chopstick[right]);
				now = time(NULL);
				strftime(time_now,100,"%H:%M:%S",localtime(&now));				
				cout<<time_now<<"-Phi "<<phi_num<<"-thinking"<<"\n";
				sleep(think_time);
			}
			else{  //even first pick right then pick left
				pthread_mutex_lock(&chopstick[right]);//take right chopstick.
				now = time(NULL);
				strftime(time_now,100,"%H:%M:%S",localtime(&now));
				pthread_mutex_lock(&output);
				cout<<time_now<<"-Phi "<<phi_num<<"-taking right chopstick"<<"\n";
				pthread_mutex_unlock(&output);
				pthread_mutex_lock(&chopstick[left]);//take right chopstick.
				now = time(NULL);
				strftime(time_now,100,"%H:%M:%S",localtime(&now));
				pthread_mutex_lock(&output);
				cout<<time_now<<"-Phi "<<phi_num<<"-taking left chopstick"<<"\n";
				pthread_mutex_unlock(&output);
				//get right & left chopstick
				now = time(NULL);
				strftime(time_now,100,"%H:%M:%S",localtime(&now));				
				pthread_mutex_lock(&output);
				cout<<time_now<<"-Phi "<<phi_num<<"-eating"<<"\n";
				pthread_mutex_unlock(&output);
				sleep(eat_time);//eating.... then put down the chopstick.
				now = time(NULL);
				strftime(time_now,100,"%H:%M:%S",localtime(&now));
				pthread_mutex_lock(&output);
				cout<<time_now<<"-Phi "<<phi_num<<"-putting right chopstick"<<"\n";			
				pthread_mutex_unlock(&output);
				pthread_mutex_unlock(&chopstick[right]);
				now = time(NULL);
				strftime(time_now,100,"%H:%M:%S",localtime(&now));
				pthread_mutex_lock(&output);
				cout<<time_now<<"-Phi "<<phi_num<<"-putting left chopstick"<<"\n";
				pthread_mutex_unlock(&output);
				pthread_mutex_unlock(&chopstick[left]);
				now = time(NULL);
				strftime(time_now,100,"%H:%M:%S",localtime(&now));				
				cout<<time_now<<"-Phi "<<phi_num<<"-thinking"<<"\n";
				sleep(think_time);
			}
		}
		break;
		case 3:
		for(int i=0;i<10;i++){
			think_time = rand()%(10-5+1)+5; eat_time = rand()%(5-1+1)+1;

			
			while(true){
				while(!pthread_mutex_trylock(&chopstick[left]));
				if(!pthread_mutex_trylock(&chopstick[right]))
				{	
					break;
				}
				else
				{
					pthread_mutex_unlock(&chopstick[left]);
				}
				
			}
			now = time(NULL);
			strftime(time_now,100,"%H:%M:%S",localtime(&now));
			pthread_mutex_lock(&output);
			cout<<time_now<<"-Phi "<<phi_num<<"-taking two chopsticks"<<"\n";
			pthread_mutex_unlock(&output);
			
			//get right & left chopstick
			now = time(NULL);
			strftime(time_now,100,"%H:%M:%S",localtime(&now));				
			pthread_mutex_lock(&output);
			cout<<time_now<<"-Phi "<<phi_num<<"-eating"<<"\n";
			pthread_mutex_unlock(&output);
			sleep(eat_time);//eating.... then put down the chopstick.
			now = time(NULL);
			strftime(time_now,100,"%H:%M:%S",localtime(&now));
			pthread_mutex_lock(&output);
			cout<<time_now<<"-Phi "<<phi_num<<"-putting left chopstick"<<"\n";			
			pthread_mutex_unlock(&output);
			pthread_mutex_unlock(&chopstick[left]);
			now = time(NULL);
			strftime(time_now,100,"%H:%M:%S",localtime(&now));
			pthread_mutex_lock(&output);
			cout<<time_now<<"-Phi "<<phi_num<<"-putting right chopstick"<<"\n";
			pthread_mutex_unlock(&output);
			pthread_mutex_unlock(&chopstick[right]);
			now = time(NULL);
			strftime(time_now,100,"%H:%M:%S",localtime(&now));
			pthread_mutex_lock(&output);				
			cout<<time_now<<"-Phi "<<phi_num<<"-thinking"<<"\n";
			pthread_mutex_unlock(&output);
			sleep(think_time);
		}
		break;
		default:
		cout<<"error occurred."<<endl;
		pthread_exit(NULL);
		break;
	}
	now = time(NULL);
	strftime(time_now,100,"%H:%M:%S",localtime(&now));
	pthread_mutex_lock(&output);
	cout<<time_now<<"-Phi "<<phi_num<<"-leaving..."<<"\n";	
	pthread_mutex_unlock(&output);
	pthread_exit(NULL);
}
int main(int argc,char* argv[])
{
	srand(0); //set random seeds
	int m,n=0;
	m = stoi(argv[1]);
	n = stoi(argv[2]);
	if(m<1 || m>3 || n<3 || n>11)
	{
		cout<<"outrange error... program exit.";
		return 0;
	}
	cout<<"*****This is algorithm-"<<m<<" case*****"<<"\n";
	pthread_t work_thread[n];
	parameter args[n];
	/*set work thread*/
	for(int i=0;i<n;i++)
	{
		args[i].number = i+1;
		args[i].algorithms=m;
		args[i].total_nums=n;
		if(pthread_create(&work_thread[i],NULL,algorithm,(void*)&args[i])){
				cerr<<"error occurred by work"<<i<<"\n";
		};
	}
	for (int i = 0 ;i<n;i++)
		pthread_join(work_thread[i], NULL);
	return 0;
};

