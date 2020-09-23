// Harlie Hardage
// CPSC 6125 OS
// September 21, 2020
// Discussion 3 - Dining Philosophets

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <pthread.h>

# define N 5
# define THINKING 2
# define HUNGRY 1 
# define EATING 0
# define LEFT (i + 4) % N
# define RIGHT (i + 1) % N

void check(int);
void pickup(int);
void putdown(int);
void* phil(void* num);

int state[N];
int philosophers[N] = { 0, 1, 2, 3, 4 };

sem_t mutex;
sem_t sem[N];

int main() {

	int i;
	pthread_t thread_id[N];
	
	sem_init(&mutex, 0, 1);
	
	for (i = 0; i < N; i++) {
		
		sem_init(&sem[i], 0, 0);
		
		pthread_create(&thread_id[i], NULL, phil, &philosophers[i]);
		
		printf("Philosopher %d: I am thinking.\n", i + 1);
		
	}
	
	for (i = 0; i < N; i++) {
		pthread_join (thread_id[i], NULL); 
	}
}

void pickup(int i) { // pick up chopsticks
	
	sem_wait(&mutex);
	state[i] = HUNGRY;
	
	printf("Philosopher %d: I am hungry.\n", i + 1);
	
	check(i);
	
	sem_post(&mutex);
	
	sem_wait(&sem[i]);
	
	sleep(1);
}	
	
void putdown(int i) { // put down chopsticks

	sem_wait(&mutex);
	state[i] = THINKING;
	
	printf("Philosopher %d: *puts down %d and %d chopsticks* I am thinking.\n", i + 1, LEFT + 1, i + 1);
	
	check(RIGHT);
	check(LEFT);
	
	sem_post(&mutex);
}

void check (int i) { // check if philosopher can eat

	if ( state[i]==HUNGRY && state[RIGHT]!=EATING && state[LEFT]!=EATING ) {
		state[i] = EATING;
		
		sleep(1);
		
		printf("Philosopher %d: *picks up %d and %d chopsticks* I am eating.\n", i + 1, LEFT + 1, i + 1);
		sem_post(&sem[i]);
	}	
}
	
void* phil(void* num) {

	int* i = num;

	while (1) {

		sleep(1);
		pickup(*i);
		sleep(1);
		putdown(*i);
		
	}
}
