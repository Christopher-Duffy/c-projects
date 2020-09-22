#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

pthread_t philosophers[5];
pthread_mutex_t chopsticks[5];
int getLeftIndex(int i){
	if(i==0){
		return 4;
	}else{
		return i-1;
	}
}
int getRightIndex(int i){
	return i;
}

void * begin(void * num){
	int n = (int) *((unsigned int *) num);
	int l=getLeftIndex(n);
	int r=getRightIndex(n);
	printf("I am %d, and I'm trying to grab %d and %d\n",n,l,r);
	int iHaveLeft=0;
	int iHaveRight=0;
	int leftTaken;
	int rightTaken;
	while(iHaveLeft==0 || iHaveRight==0){
		printf("%d Thinking\n", n);
		sleep(rand()%5);
		printf("%d Try to take left chopstick\n",n);
		leftTaken = pthread_mutex_trylock(&chopsticks[l]);
		if(!leftTaken){
			iHaveLeft=1;
		}
		sleep(rand()%5);
		printf("%d Try to take right chopstick\n",n);
		rightTaken = pthread_mutex_trylock(&chopsticks[r]);
		if(!rightTaken){
                        iHaveRight=1;
                }
		sleep(rand()%5);
		printf("left:%d right:%d\n",leftTaken,rightTaken);
		if (!(leftTaken && rightTaken) && (leftTaken || rightTaken)){
			//take left
			if(iHaveLeft){
				printf("%d Giving up left chopstick\n", n);
				pthread_mutex_unlock(&chopsticks[l]);
				iHaveLeft=0;
				sleep(rand()%5);
			}else if(iHaveRight){
				printf("%d Giving up Right chopstick\n", n);
				pthread_mutex_unlock(&chopsticks[r]);
				iHaveRight=0;
				sleep(rand()%5);
			}
		}
	}
	printf("I have eaten\n");
	printf("%d Giving up left chopstick\n", n);
	pthread_mutex_unlock(&chopsticks[l]);
	printf("%d Giving up right chopstick\n", n);
	pthread_mutex_unlock(&chopsticks[r]);
	pthread_exit(NULL);
}

int main(){
	for(int i=0;i<5;i++){
                pthread_mutex_init(&chopsticks[i], NULL);
        }
	unsigned int ints[5];
	for(int i=0;i<5;i++){
		ints[i]=i;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		if(pthread_create(&(philosophers[i]),&attr,&begin,&ints[i])!=0){
			printf("something went wrong");
			return 1;
		}
	}
	for(int i=0;i<5;i++){
		pthread_join(philosophers[i], NULL);
	}
	
}
