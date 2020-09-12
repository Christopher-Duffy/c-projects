#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <string.h>

#define SIZE 10
#define NAME_SIZE 20

struct user {
  int userId;
  char userName[NAME_SIZE];
};

void populate(struct user* users, int size){
  for (int i =0; i< size; i++){
    printf("Enter a user id for user number %d:\n",i);
    scanf("%d",&users->userId);
    printf("Enter a username for user number %d:\n",i);
    scanf("%s",users->userName);
    ++users;
  }
}

void writeArr(struct user* users, int size){
  for (int i =0; i< size; i++){
    printf("%d ",users->userId);
    printf("%s\n",users->userName);
    ++users;
  }
}

void* createSharedMemory(size_t size){
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANONYMOUS;
  return mmap(NULL, size, protection, visibility,-1,0);
}

int main(void){
  struct user usersArray[SIZE];
  void *sharedUsers = createSharedMemory(sizeof(usersArray));
  memcpy(sharedUsers, usersArray, sizeof(usersArray));
  struct user* users = sharedUsers;
  
  pid_t pid = fork();
  
  if(pid==0){
    //child process
    populate(sharedUsers,SIZE);
  } else if (pid>0){
    //parent process
    int status;
    waitpid(pid, &status,0);
    if ( WIFEXITED(status) ){
    	const int es = WEXITSTATUS(status);
    	printf("Exit status was %d\n", es);
    }
    printf("Child pid was %d\n", pid);

  }else{
    printf("The fork did not succeed.\n");
  }
  munmap(sharedUsers,sizeof(usersArray));
  return 0;
}
