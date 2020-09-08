#include <stdio.h>
#include <stdlib.h>

struct user {
  int user_id;
  char* user_name;
};

int getIDFromUser(void){
  //set up a 'string'
  char inputBuffer[32];
  char *ptr;
  int number=0;
  printf("Enter an integer for user_id.\n");
  //grab the whole line
  fgets(inputBuffer, sizeof(inputBuffer), stdin);
  //parse out an int, if no int number will be 0
  number = strtol(inputBuffer,&ptr,10);
  return number;
}

char* getNameFromUser(char* ptr){
  //set up a 'string'
  char inputBuffer[32];
  //char *ptr;
  printf("Enter the Users name.\n");
  //grab the whole line
  fgets(inputBuffer, sizeof(inputBuffer), stdin);
  ptr = malloc(sizeof(inputBuffer));
  ptr = inputBuffer;
  return ptr;
}

void populate(struct user* users, int size){
  for (struct user* i = users; i < (users+size); i++){
    i->user_id = getIDFromUser();
    i->user_name = getNameFromUser(i->user_name);
    char* ptr = i->user_name;
    while(*ptr!='\0'){
    	printf("%c",*ptr++);
    }
  }
}

void printUsers(struct user* users, int size){
  for (struct user* i = users; i < (users+size); i++){
    printf("%d: ",i->user_id);
    char *ptr = i->user_name;
    printf("%s",ptr);
    printf("\n");
  }
}

int main(){
  int size = 3;
  struct user users[size];
  struct user* users_ptr = users;
  populate ( users_ptr,size );
  printUsers( users_ptr,size );
  return 0;
}
