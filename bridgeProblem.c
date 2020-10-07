#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int NORTH = 0;
int SOUTH = 1;
int light = 2;
int trafficDirection = 0;

void* trafficLight(void* threadIndex) 
{ 
    while(1){
      if(trafficDirection == NORTH){
        trafficDirection = SOUTH;
      }else{
        trafficDirection = NORTH;
      }
      sleep(5);
    }
}

void* simulateTraffic(void* threadIndex) 
{ 
    int *direction = threadIndex;
    while(1){
      if(*direction == NORTH){
        printf("This is the North-going thread: \n");
      } else{
        printf("This is the South-going thread: \n");
      }
      if (*direction == trafficDirection){
      	printf(" - My light is green\n");
      } else{
        printf(" - My light is red\n");
      }
      sleep(1);
    }
} 
 
int main() 
{  
  srand(time(0));
  pthread_t north_thread_id;
  pthread_t south_thread_id;
  pthread_t traffic_light_thread_id;
  
  //create threads
    if(pthread_create(&north_thread_id, NULL, simulateTraffic, &NORTH)!=0){
      printf("There was an error creating a thread");
      return 1;
    } 
    if(pthread_create(&south_thread_id, NULL, simulateTraffic, &SOUTH)!=0){
      printf("There was an error creating a thread");
      return 1;
    }
    if(pthread_create(&traffic_light_thread_id, NULL, trafficLight, &light)!=0){
      printf("There was an error creating a thread");
      return 1;
    }
  //join threads
    pthread_join(north_thread_id, NULL);
    pthread_join(south_thread_id, NULL);
    pthread_join(traffic_light_thread_id, NULL); 
} 
