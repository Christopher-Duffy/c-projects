#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h>
#include <unistd.h>
  
#define NUM_THREADS 5 
#define LEFT (threadIndex + 4) % NUM_THREADS
#define RIGHT (threadIndex + 1) % NUM_THREADS 
#define WANT 0
#define HAS 1
#define IDLE 2


int stateLedger[NUM_THREADS]; 
int thread[NUM_THREADS] = { 0, 1, 2, 3, 4 }; //this will have to be edited for a different n 
  
pthread_mutex_t stateLedgerLock; 
pthread_mutex_t spoonLocks[NUM_THREADS]; 
  

void wantSpoons(int threadIndex){
  pthread_mutex_lock(&stateLedgerLock);
  stateLedger[threadIndex] = WANT;
  printf("Philosopher %d wants spoons\n", threadIndex + 1); 
  pthread_mutex_unlock(&stateLedgerLock);
  
}
int claimSpoons(int threadIndex){
  pthread_mutex_lock(&stateLedgerLock);
  if (stateLedger[threadIndex] == WANT && stateLedger[LEFT] != HAS && stateLedger[RIGHT] != HAS) { 
    stateLedger[threadIndex] = HAS;  
    printf("Philosopher %d claims spoon %d and %d\n", threadIndex + 1, LEFT + 1, threadIndex + 1);
    pthread_mutex_unlock(&stateLedgerLock);
    return 1;
  }
  pthread_mutex_unlock(&stateLedgerLock);
  return 0;  
}
void takeSpoons(int threadIndex){
  pthread_mutex_lock(&spoonLocks[LEFT]);
  pthread_mutex_lock(&spoonLocks[threadIndex]);
  printf("Philosopher %d picks up spoon %d and %d\n", threadIndex + 1, LEFT + 1, threadIndex + 1);
  sleep(2);
  pthread_mutex_lock(&stateLedgerLock);
  stateLedger[threadIndex] = IDLE;
  printf("Philosopher %d sets down spoon %d and %d\n", threadIndex + 1, LEFT + 1, threadIndex + 1);
  pthread_mutex_unlock(&spoonLocks[LEFT]);
  pthread_mutex_unlock(&spoonLocks[threadIndex]);
  pthread_mutex_unlock(&stateLedgerLock);
}

void* obtainSpoons(void* num) 
{ 
    int *threadIndex = num;
    wantSpoons(*threadIndex);
    if(claimSpoons(*threadIndex)){
      takeSpoons(*threadIndex);
    }else{
      sleep(2);
      obtainSpoons(num);
    }
  } 
 
int main() 
{ 
  int i; 
  pthread_t thread_id[NUM_THREADS]; 
  if(pthread_mutex_init(&stateLedgerLock,NULL) !=0){
    printf("There was an error with mutex init");
    return 1;
  } 
  for (i = 0; i < NUM_THREADS; i++){
    if(pthread_mutex_init(&spoonLocks[i],NULL) !=0){
      printf("There was an error with mutex init");
      return 1;
    } 
  }
  //create threads
  for (i = 0; i < NUM_THREADS; i++) { 
    if(pthread_create(&thread_id[i], NULL, obtainSpoons, &thread[i])!=0){
      printf("There was an error creating a thread");
      return 1;
    } 
  } 
  //join threads
  for (i = 0; i < NUM_THREADS; i++){
    pthread_join(thread_id[i], NULL);
  } 
} 
